#ifndef OBSLUGA_CZASU_H
#define OBSLUGA_CZASU_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDateTime>

class obsluga_czasu : public QObject
{
    Q_OBJECT
public:
    explicit obsluga_czasu(QObject *parent = 0);
    QDate aktualna_data;        //przechowuje aktualna date
    QTime aktualna_godzina;     //przechowuje aktualna godzine


signals:


public slots:

public:
    QDate podaj_aktualna_date(); //podaje date i wysyła sygnał aktualizacji
    QTime podaj_czas(); //podaje godzine i wysyła sygnał aktualizacji

};

#endif // OBSLUGA_CZASU_H
