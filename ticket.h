#ifndef TICKET_H
#define TICKET_H
#include <QStringList>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
class Ticket
{
    int id;
    int id_client;
    int id_event;
public:
    Ticket();
    Ticket(int,int,int);
    Ticket(int,int);

    QStringList ClientList();
    QStringList EvenementList();
    void        printTicket(int, int, QString);
    bool ajouter();
    QChart* chart();
};

#endif // TICKET_H
