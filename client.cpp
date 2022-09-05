#include "client.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>

Client::Client(){}

Client::Client(int id, QString nom, QString prenom, int numero, QString email)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->numero=numero;
    this->email=email;
}

Client::Client(QString nom, QString prenom, int numero, QString email)
{
    this->nom=nom;
    this->prenom=prenom;
    this->numero=numero;
    this->email=email;
}

bool Client::ajouter()
{
    QSqlQuery query;
    if(nom.isEmpty())
    {
        QMessageBox::information(nullptr,"erreur","le nom ne doit pas être vide.");
        return false;
    }
    else if(prenom.isEmpty())
    {
        QMessageBox::information(nullptr,"erreur","le prenom ne doit pas être vide.");
        return false;
    }
    else if(numero <=0)
    {
        return false;
    }
    else if(email.isEmpty())
    {
        QMessageBox::information(nullptr,"erreur","le email ne doit pas être vide.");
        return false;
    }
    else
    {
        query.prepare("INSERT INTO les_clients (nom, prenom, numero, email) VALUES (:nom, :prenom, :numero, :email)");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":numero",numero);
        query.bindValue(":email",email);

        return query.exec();
    }


}

QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from les_clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("numero"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));

    return model;
}

 bool Client::supprimer(int id)
 {
    QSqlQuery query;
    query.prepare("DELETE FROM les_clients WHERE id=:id ");
    query.bindValue(":id",       id);

    return query.exec();
 }

 bool Client::modifier(int id, QString nom, QString prenom, int numero, QString email)
 {
     QSqlQuery query;
     if(nom.isEmpty())
     {
         QMessageBox::information(nullptr,"erreur","le nom ne doit pas être vide.");
         return false;
     }
     else if(prenom.isEmpty())
     {
         QMessageBox::information(nullptr,"erreur","le prenom ne doit pas être vide.");
         return false;
     }
     else if(numero <=0)
     {
         return false;
     }
     else if(email.isEmpty())
     {
         QMessageBox::information(nullptr,"erreur","le email ne doit pas être vide.");
         return false;
     }
     else
     {
         query.prepare("UPDATE les_clients SET nom=:nom, prenom=:prenom, email=:email, numero=:numero WHERE id=:id");
         query.bindValue(":id",  id);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom",prenom);
         query.bindValue(":numero",numero);
         query.bindValue(":email",email);

         return query.exec();
     }
 }

 QSqlQueryModel * Client::recherche(QString nom, QString prenom, int numero, QString email)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     QSqlQuery query;

     query.prepare("select * from les_clients where (  (prenom = :prenom) OR (numero = :numero) OR (email = :email) OR (nom = :nom)) ");
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":numero",numero);
     query.bindValue(":email",email);

     query.exec();

     model->setQuery(query);

     model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("numero"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));

     return model;
 }
 QSqlQueryModel * Client::trier(QString OrderBy)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     QSqlQuery query;

     query.prepare("select * from les_clients order by numero ;");
     query.bindValue(":o",OrderBy);
     query.exec();
qDebug() << OrderBy;
     model->setQuery(query);

     model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("numero"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));

     return model;
 }
