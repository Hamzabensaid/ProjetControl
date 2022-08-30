#include "evenement.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
Evenement::Evenement(){}

Evenement::Evenement(int id, QString titre, QDate event_date, int capacite, QString description, double prix)
{
    this->id = id;
    this->titre = titre;
    this->event_date = event_date;
    this->capacite = capacite;
    this->description = description;
    this->prix = prix;
}

Evenement::Evenement(QString titre, QDate event_date, int capacite, QString description, double prix)
{
    this->titre = titre;
    this->event_date = event_date;
    this->capacite = capacite;
    this->description = description;
    this->prix = prix;
}

bool Evenement::ajouter()
{

    if(titre.isEmpty())
    {
        QMessageBox::information(nullptr,"erreur","le titre ne doit pas être vide.");
        qDebug() << "T EMPTY";
        return false;
    }
    else if(event_date < QDate::currentDate())
    {
        QMessageBox::information(nullptr,"erreur","la date doit être postérieure à aujourd'hui");
        qDebug() << "DAATE MUST BE AFTER CURRENT DATE";
        return false;
    }
    else if(prix < 1 )
    {
        QMessageBox::information(nullptr,"erreur","1 < prix");
        return false;
    }
    else if(capacite < 1 || capacite > 1000 )
    {
        QMessageBox::information(nullptr,"erreur","1 < capacite < 1000");
        qDebug() << "cap out of rage";
        return false;
    }
    else if(description.isEmpty())
    {
        QMessageBox::information(nullptr,"erreur","le Description ne doit pas être vide.");
        qDebug() << "D EMPTY";
        return false;
    }
    else
    {
        QSqlQuery query;
        query.prepare("INSERT INTO evenements (titre, event_date, capacite, description, prix) VALUES (:titre, :event_date, :capacite, :description, :prix)");
        query.bindValue(":titre", titre);
        query.bindValue(":event_date",event_date);
        query.bindValue(":capacite",capacite);
        query.bindValue(":description",description);
        query.bindValue(":prix",prix);
        return query.exec();
    }



}

QSqlQueryModel * Evenement::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from evenements");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("capacite"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix (dt)"));

    return model;
}

 bool Evenement::supprimer(int id)
 {
    QSqlQuery query;
    query.prepare("DELETE FROM evenements WHERE id=:id ");
    query.bindValue(":id",       id);

    return query.exec();
 }

 bool Evenement::modifier(int id, QString titre, QDate event_date, int capacite, QString description, double prix)
 {
     QSqlQuery query;
     if(titre.isEmpty())
     {
         QMessageBox::information(nullptr,"erreur","le titre ne doit pas être vide.");
         return false;
     }
     else if(event_date < QDate::currentDate())
     {
         QMessageBox::information(nullptr,"erreur","la date doit être postérieure à aujourd'hui");
         return false;
     }
     else if(prix < 1 )
     {
         QMessageBox::information(nullptr,"erreur","1 < prix");
         return false;
     }
     else if(capacite < 1 || capacite > 1000 )
     {
         QMessageBox::information(nullptr,"erreur","1 < capacite < 1000");
         return false;
     }
     else if(description.isEmpty())
     {
         QMessageBox::information(nullptr,"erreur","le Description ne doit pas être vide.");
         return false;
     }
     else
     {
     query.prepare("UPDATE evenements SET titre=:titre, event_date=:event_date, capacite=:capacite, description=:description, prix=:prix WHERE id=:id");
     query.bindValue(":id",  id);
     query.bindValue(":titre", titre);
     query.bindValue(":event_date",event_date);
     query.bindValue(":capacite",capacite);
     query.bindValue(":description",description);
     query.bindValue(":prix",prix);

     return query.exec();
     }
 }

 QSqlQueryModel * Evenement::recherche(QString titre, int capacite, QString description, double prix)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     QSqlQuery query;

     query.prepare("select * from evenements where ((titre = :titre) OR (prix = :prix) OR (capacite = :capacite) OR (description = :description)) order by titre");
     query.bindValue(":titre", titre);
     query.bindValue(":capacite",capacite);
     query.bindValue(":description",description);
     query.bindValue(":prix",prix);

     query.exec();

     model->setQuery(query);

     model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("capacite"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("prix (dt)"));
     return model;
 }

