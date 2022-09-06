#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "client.h"
#include "evenement.h"
#include "ticket.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Client CLIENT;
    Evenement EVENT;
    Ticket    TICKET;
    QChartView *chartview;

private slots:
    void on_ClientsButton_clicked();

    void on_EventsButton_clicked();

    void on_TicketsButton_clicked();

    void on_ClientAddButton_clicked();

    void on_ClientDeleteButton_clicked();


    void on_ClientUpdateButton_clicked();

    void on_ClientModifierButton_clicked();

    void on_SearchClientButton_clicked();

    void on_EventAddButton_clicked();

    void on_EventUpdateButton_clicked();

    void on_EventModifierButton_clicked();

    void on_EventDeleteButton_clicked();

    void on_SearchEventButton_clicked();

    void on_PrintTicketButton_clicked();

    void on_TriClientButton_clicked();

    void on_TriEventButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
