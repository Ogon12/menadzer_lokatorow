#include "obsluga_czasu.h"
#include "QDateEdit"

obsluga_czasu::obsluga_czasu(QObject *parent) : QObject(parent)
{
    aktualna_data = QDate::currentDate();       //pobiera aktualna date

    aktualna_godzina = QTime::currentTime();    //pobiera aktualna godzine


}

QDate obsluga_czasu::podaj_aktualna_date()
{
    return aktualna_data;
}
