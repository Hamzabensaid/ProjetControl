#include "ticket.h"
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QObject>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

Ticket::Ticket(){}

Ticket::Ticket(int id_client, int id_event)
{
    this->id_client = id_client;
    this->id_event  = id_event;
}

QStringList Ticket::ClientList()
{
    QStringList List ;
    QSqlQuery qry;
    qry.prepare("SELECT id FROM  les_clients");
    if(!qry.exec())
    {
        QMessageBox::information(nullptr,"Error","Failed to exec query");
    }
    else
    {
        while(qry.next())
        {
        List.append(
                    qry.value(0).toString()
                    );
        }
    }
    return List;
}

QStringList Ticket::EvenementList()
{
    QStringList List ;
    QSqlQuery qry;
    qry.prepare("SELECT id FROM  evenements");
    if(!qry.exec())
    {
        QMessageBox::information(nullptr,"Error","Failed to exec query");
    }
    else
    {
        while(qry.next())
        {
        List.append(
                    qry.value(0).toString()
                    );
        }
    }
    return List;
}

#include "QrCodeGenerator/QrCode.h"

void paintQR(QPainter &painter, const QSize sz, const QString &data, QColor fg)
{
    // NOTE: At this point you will use the API to get the encoding and format you want, instead of my hardcoded stuff:
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.toUtf8().constData(), qrcodegen::QrCode::Ecc::LOW);
    const int s=qr.getSize()>0?qr.getSize():1;
    const double w=sz.width();
    const double h=sz.height();
    const double aspect=w/h;
    const double size=((aspect>1.0)?h:w);
    const double scale=size/(s+2);
    // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
    // It expects background to be prepared already (in white or whatever is preferred).
    painter.setPen(Qt::NoPen);
    painter.setBrush(fg);
    for(int y=0; y<s; y++) {
        for(int x=0; x<s; x++) {
            const int color=qr.getModule(x, y);  // 0 for white, 1 for black
            if(0!=color) {
                const double rx1=(x+1)*scale, ry1=(y+1)*scale;
                QRectF r(rx1+7500, ry1+1800, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
}




void Ticket::printTicket(int id_C, int id_E, QString link)
{
    QPdfWriter pdf(link);
    QPainter painter(&pdf);

    QImage  temp(":/new/prefix1/TemplateBadge.png");
    painter.drawImage(QRect(100, 50,temp.width()*(3000.0/temp.height()), 3000), temp);
    QSqlQuery EventQry;
    EventQry.prepare("SELECT * FROM  evenements WHERE id = :id");
    EventQry.bindValue(":id",id_E);
    if(!EventQry.exec())
    {
        QMessageBox::information(nullptr,"Error","Failed to exec query");
    }
    else
    {
        while(EventQry.next())
        {
            painter.setFont(QFont("Gabriola", 37));
            painter.setPen(QPen(QColor("#ffffff")));
            painter.drawText(3020,950,EventQry.value(EventQry.record().indexOf("titre")).toString());

            painter.setFont(QFont("Gabriola", 10));
            painter.setPen(QPen(QColor("#ffffff")));
            painter.drawText(3000,950,3650,1400,Qt::TextWordWrap, EventQry.value(EventQry.record().indexOf("description")).toString());

            painter.setFont(QFont("Gabriola", 14));
            painter.setPen(QPen(QColor("#ffffff")));
            painter.drawText(2700,2000,3650,1400,Qt::TextWordWrap, EventQry.value(EventQry.record().indexOf("event_date")).toString());

            painter.setFont(QFont("Nirmala UI Semilight", 37));
            painter.setPen(QPen(QColor("#ffffff")));
            painter.drawText(7300,1100,EventQry.value(EventQry.record().indexOf("prix")).toString()+" DT");
        }
    }
    paintQR(painter,QSize(1000,1000),QString::number(id_C),QColor("white"));
    painter.end();
    QDesktopServices::openUrl(link);
}

bool Ticket::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO les_tickets (id_client, id_event) VALUES (:id_client, :id_event)");
    query.bindValue(":id_client", id_client);
    query.bindValue(":id_event",id_event);


    return query.exec();
}
QChart* Ticket::chart()
{
    QPieSeries *series = new QPieSeries();
    series->setLabelsVisible(true);

    QSqlQuery EventQry;
    EventQry.prepare("SELECT * FROM  evenements");
    if(!EventQry.exec())
    {
        QMessageBox::information(nullptr,"Error","Failed to exec query");
    }
    else
    {

        while(EventQry.next())
        {
            QSqlQuery TicketQry;
            TicketQry.prepare("SELECT * FROM  les_tickets where id_event=:id_event");
            TicketQry.bindValue(":id_event", EventQry.value(EventQry.record().indexOf("id")));

            if(!TicketQry.exec())
            {
                QMessageBox::information(nullptr,"Error","Failed to exec query");
            }
            else
            {
                int NumberOfTickets = 0;
                while(TicketQry.next())
                {
                    NumberOfTickets++;
                }
                series->append(EventQry.value(EventQry.record().indexOf("titre")).toString() + " "+QString::number(NumberOfTickets), NumberOfTickets);

            }

        }
    }




    series->setLabelsVisible(true);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Qt5 Pie Chart Example");

    return chart;
}
