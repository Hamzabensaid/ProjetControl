#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
    int id;
    QString nom;
    QString prenom;
    int numero;
    QString email;
public:
    Client();
    Client(int, QString, QString, int, QString);
    Client(QString, QString, int, QString);

    int getId(){return id;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getNumero(){return numero;}
    QString getEmail(){return email;}

    void setId(int id){this->id = id;}
    void setNom(QString nom){this->nom = nom;}
    void setPrenom(QString prenom){this->prenom = prenom;}
    void setNumero(int numero){this->numero = numero;}
    void setEmail(QString email){this->email = email;}

    bool ajouter();
    bool supprimer(int);
    bool modifier(int , QString , QString , int , QString );
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString , QString , int , QString);
    QSqlQueryModel * trier(QString);


};

#endif
