#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "client.h"
#include "evenement.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QFileDialog>
#include <QFile>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>

#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ClientTableView->setModel(CLIENT.afficher());

    ui->EventTableView->setModel(EVENT.afficher());

    ui->ClientComboBox->addItems(TICKET.ClientList());
    ui->EventComboBox->addItems(TICKET.EvenementList());





        chartview = new QChartView(TICKET.chart());
        chartview->setMinimumWidth(600);
        chartview->setMinimumHeight(300);
        chartview->setParent(ui->frame);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ClientsButton_clicked()
{
    ui->DashboardPages->setCurrentIndex(0);

}


void MainWindow::on_EventsButton_clicked()
{
    ui->DashboardPages->setCurrentIndex(1);
}


void MainWindow::on_TicketsButton_clicked()
{
    ui->DashboardPages->setCurrentIndex(2);
}


void MainWindow::on_StatisticButton_clicked()
{
    ui->DashboardPages->setCurrentIndex(3);
}


void MainWindow::on_ClientAddButton_clicked()
{
    QString nom = ui->ClientNomAdd->text();
    QString prenom = ui->ClientPrenomAdd->text();
    int numero = ui->ClientNumeroAdd->text().toInt();
    QString email = ui->ClientEmailAdd->text();

    Client C(nom, prenom, numero, email);



    bool test = C.ajouter();

    if(test)
    {
        ui->ClientTableView->setModel(CLIENT.afficher());

        ui->ClientComboBox->clear();
        ui->ClientComboBox->addItems(TICKET.ClientList());

        QMessageBox::information(nullptr,"Success","Client registered successfully.");

    }
    else
    {
        QMessageBox::information(nullptr,"error","database error");
    }
}


void MainWindow::on_ClientDeleteButton_clicked()
{
    if(ui->ClientTableView->selectionModel()->hasSelection())
    {

        int id = ui->ClientTableView->selectionModel()->selectedRows().value(0).data().toInt();

        bool test = CLIENT.supprimer(id);

        if(test)
        {
            ui->ClientTableView->setModel(CLIENT.afficher());

            ui->ClientComboBox->clear();
            ui->ClientComboBox->addItems(TICKET.ClientList());

            QMessageBox::information(nullptr,"Success","CLIENT SUPPRIMER");

        }
        else
        {
            QMessageBox::information(nullptr,"error","database error");
        }
    }
    else
    {
         QMessageBox::information(nullptr,"error","select client");
    }

}


void MainWindow::on_ClientUpdateButton_clicked()
{

    if(ui->ClientTableView->selectionModel()->hasSelection())
    {
        int id =         ui->ClientTableView->selectionModel()->selectedRows(0).value(0).data().toInt();
        QString nom =    ui->ClientTableView->selectionModel()->selectedRows(1).value(0).data().toString();
        QString prenom = ui->ClientTableView->selectionModel()->selectedRows(2).value(0).data().toString();
        int numero =     ui->ClientTableView->selectionModel()->selectedRows(3).value(0).data().toInt();
        QString email =  ui->ClientTableView->selectionModel()->selectedRows(4).value(0).data().toString();

        ui->ClientIdUpdate->setText(QString::number(id));
        ui->ClientNomUpdate->setText(nom);
        ui->ClientPrenomUpdate->setText(prenom);
        ui->ClientNumeroUpdate->setText( QString::number(numero));
        ui->ClientEmailUpdate->setText(email);

        ui->ClientsTabWidget->setCurrentIndex(2);

    }
    else
    {
         QMessageBox::information(nullptr,"error","select client");
    }

}


void MainWindow::on_ClientModifierButton_clicked()
{
    int id = ui->ClientIdUpdate->text().toInt();
    QString nom = ui->ClientNomUpdate->text();
    QString prenom = ui->ClientPrenomUpdate->text();
    int numero = ui->ClientNumeroUpdate->text().toInt();
    QString email = ui->ClientEmailUpdate->text();

    bool test = CLIENT.modifier(id,nom,prenom,numero,email);

    if(test)
    {
        ui->ClientTableView->setModel(CLIENT.afficher());

        ui->ClientComboBox->clear();
        ui->ClientComboBox->addItems(TICKET.ClientList());

        QMessageBox::information(nullptr,"Success","Client est modifier");

    }
    else
    {
        QMessageBox::information(nullptr,"error","database error");
    }

}


void MainWindow::on_SearchClientButton_clicked()
{
    QString nom = ui->SearchClientByNom->text();
    QString prenom = ui->SearchClientByPrenom->text();
    int numero = ui->SearchClientByNumero->text().toInt();
    QString email = ui->SearchClientByEmail->text();

    ui->ClientTableView->setModel(CLIENT.recherche(nom,prenom,numero,email));
    qDebug() << nom;

}


void MainWindow::on_EventAddButton_clicked()
{
    QString titre = ui->EventTitreAdd->text();
    QDate   event_date = ui->EventDateAdd->date();
    int capacite = ui->EventCapaciteAdd->text().toInt();
    QString description = ui->EventDescriptionAdd->text();
    double prix = ui->EventPrixAdd->text().toDouble();

    Evenement E( titre, event_date, capacite, description, prix );

    bool test = E.ajouter();

    if(test)
    {
        ui->EventTableView->setModel(EVENT.afficher());

        ui->EventComboBox->clear();
        ui->EventComboBox->addItems(TICKET.EvenementList());

        QMessageBox::information(nullptr,"Success","event registered successfully.");

    }
    else
    {
        QMessageBox::information(nullptr,"error","database error");
    }
}


void MainWindow::on_EventUpdateButton_clicked()
{

    if(ui->EventTableView->selectionModel()->hasSelection())
    {
        int     id =    ui->EventTableView->selectionModel()->selectedRows(0).value(0).data().toInt();
        QString titre = ui->EventTableView->selectionModel()->selectedRows(1).value(0).data().toString();
        QDate   event_date = ui->EventTableView->selectionModel()->selectedRows(2).value(0).data().toDate();
        int     capacite = ui->EventTableView->selectionModel()->selectedRows(3).value(0).data().toInt();
        QString description = ui->EventTableView->selectionModel()->selectedRows(4).value(0).data().toString();
        double prix = ui->EventTableView->selectionModel()->selectedRows(5).value(0).data().toDouble();


        ui->EventIdUpdate->setText(QString::number(id));
        ui->EventTitreUpdate->setText(titre);
        ui->EventDateUpdate->setDate(event_date);
        ui->EventCapaciteUpdate->setText(QString::number(capacite));
        ui->EventDescriptionUpdate->setText(description);
        ui->EventPrixUpdate->setText(QString::number(prix));
        ui->EventsTabWidget->setCurrentIndex(2);
    }
    else
    {
        QMessageBox::information(nullptr,"error","select Evenement");
    }



}


void MainWindow::on_EventModifierButton_clicked()
{

    int     id = ui->EventIdUpdate->text().toInt();
    QString titre = ui->EventTitreUpdate->text();
    QDate   event_date = ui->EventDateUpdate->date();
    int capacite = ui->EventCapaciteUpdate->text().toInt();
    QString description = ui->EventDescriptionUpdate->text();
    double prix = ui->EventPrixUpdate->text().toDouble();

    bool test = EVENT.modifier(id, titre, event_date, capacite, description, prix);

    if(test)
    {
        ui->EventTableView->setModel(EVENT.afficher());

        ui->EventComboBox->clear();
        ui->EventComboBox->addItems(TICKET.EvenementList());

        QMessageBox::information(nullptr,"Success","event registered successfully.");

    }
    else
    {
        QMessageBox::information(nullptr,"error","database error");
    }
}


void MainWindow::on_EventDeleteButton_clicked()
{
    if(ui->EventTableView->selectionModel()->hasSelection())
    {

        int id = ui->EventTableView->selectionModel()->selectedRows().value(0).data().toInt();

        bool test = EVENT.supprimer(id);

        if(test)
        {
            ui->EventTableView->setModel(EVENT.afficher());

            ui->EventComboBox->clear();
            ui->EventComboBox->addItems(TICKET.EvenementList());

            chartview->setChart(TICKET.chart());
            QMessageBox::information(nullptr,"Success","Evenement SUPPRIMER");
        }
        else
        {
            QMessageBox::information(nullptr,"error","database error");
        }
    }
    else
    {
         QMessageBox::information(nullptr,"error","select event");
    }
}


void MainWindow::on_SearchEventButton_clicked()
{
    QString titre = ui->SearchEventByTitre->text();
    int capacite = ui->SearchEventByCapacite->text().toInt();
    QString description = ui->SearchEventByDescription->text();
    double prix = ui->SearchEventByPrix->text().toDouble();

    ui->EventTableView->setModel(EVENT.recherche(titre, capacite, description, prix));



}


void MainWindow::on_PrintTicketButton_clicked()
{
    QString link =QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)+"/"+"test"+".pdf";

    int clientID = ui->ClientComboBox->currentText().toInt();
    int EvenementID = ui->EventComboBox->currentText().toInt();

    TICKET.printTicket(clientID,EvenementID,link);


    Ticket T(clientID, EvenementID);

    bool test = T.ajouter();

    if(test)
    {
        chartview->setChart(TICKET.chart());

        QMessageBox::information(nullptr,"Success","Ticket registered successfully.");

    }
    else
    {
        QMessageBox::information(nullptr,"error","database error");
    }
}

