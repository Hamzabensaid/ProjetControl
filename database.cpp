#include "database.h"



Connection::Connection(){}

bool Connection::CreateConnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;

    db.setUserName("system");
    db.setPassword("0000");
    db.setDatabaseName("database_s1");


    if(db.open())
    {
        qDebug()<<"Database opened!";
        test = true;
    }
    else
    {
        qDebug() << db.lastError().text();
    }

    return test;
}


void Connection::CloseConnection()
{
    db.close();
}
