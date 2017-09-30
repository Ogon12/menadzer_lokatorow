#include "operacje_na_plikach.h"
#include "QFile"
#include "QDebug"
#include "QString"
#include <QTextStream>
#include <mainwindow.h>

//#include <io.h> // win32
//#else
#include <unistd.h> //unix
//#endif


Operacje_na_plikach::Operacje_na_plikach(QWidget *parent) : QMainWindow(parent)
{
       sciezka_nazwa_bazy_lokatorow = "";
}
Operacje_na_plikach::~Operacje_na_plikach()
{
    qDebug() << "Destruktor: Operacje na plikach";
}




bool Operacje_na_plikach::plik_wczytaj()
{
    QFile baza_lokatorow(sciezka_nazwa_bazy_lokatorow);
    if (!baza_lokatorow.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Blad otwarcia pliku";
        return false;
    }else
    {
        qDebug() << "Plik otworzony";
        while (!baza_lokatorow.atEnd()) {
        QByteArray line = baza_lokatorow.readLine();
        baza_lokatorow.close();
        }
        return true;
    }
}

bool Operacje_na_plikach::dopisz_nowego_lokatora(QString dane)
{
    //QString lokator_do_zapisu = QString("%1%2%2%3%4").arg(nazwisko).arg(imie).arg(nr_pokoju).arg(data_meldunuku);

    //SPRAWDZENIE W BAZIE CZY JUŻ ISTNIEJE
        //otworzenie bazy do odczytu
        //przeszukanie bazy po nazwisku i imieniu

    //Zapis danych do bazy
    if(sprawdz_czy_plik_istnieje(sciezka_nazwa_bazy_lokatorow))
    {
        qDebug("plik istnieje");
    }

    QFile baza_lokatorow("./baza_lokatorow.txt");
    if (!baza_lokatorow.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Blad otwarcia pliku";
        return 0;
    }else
    {
        qDebug() << "Plik otworzony tylko do zapisu.";
        //POŁĄCZENIE DANYCH


        QTextStream plik(&baza_lokatorow); //strumień zapisu danych do pliku
        plik << dane << endl;
        baza_lokatorow.close();
        return true;
     }
}

QString Operacje_na_plikach::wyszukaj_lokatora(QString parametr_wyszukiwania)
{
    return parametr_wyszukiwania;
}

void Operacje_na_plikach::pobierz_sciezke_bazy_lokatorow(QString &nowa_sciezka_i_nazwa_bazy_lokatorow)
{
    sciezka_nazwa_bazy_lokatorow = nowa_sciezka_i_nazwa_bazy_lokatorow;
}

bool Operacje_na_plikach::sprawdz_czy_plik_istnieje(QString sciezka_nazwa_pliku)
{
    if(QFile::exists(sciezka_nazwa_pliku)){
        return true;
    }else
    {
        return false;
    }
}
