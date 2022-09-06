#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Evenement
{
    int id;
    QString titre;
    QDate event_date;
    int capacite;
    QString description;
    double prix;


public:
    Evenement();
    Evenement(int, QString, QDate, int, QString, double);
    Evenement(QString, QDate, int, QString, double);

    int getId(){return id;}
    QString getTitre(){return titre;}
    QDate getEvent_date(){return event_date;}
    int getCapacite(){return capacite;}
    QString getDescription(){return description;}
    double  getPrix(){return prix;}

    void setId(int id){this->id = id;}
    void setTitre(QString titre){this->titre = titre;}
    void setEvent_date(QDate event_date){this->event_date = event_date;}
    void setCapacite(int capacite){this->capacite = capacite;}
    void setPrix(double prix){this->prix = prix;}

    bool ajouter();
    bool supprimer(int);
    bool modifier(int, QString, QDate, int, QString, double);
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString, int, QString, double);
    QSqlQueryModel * trier(QString);
};

#endif // EVENEMENT_H
