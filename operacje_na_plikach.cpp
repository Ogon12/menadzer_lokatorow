#include "operacje_na_plikach.h"
#include "QFile"
#include "QDebug"
#include "QString"
#include <QStringList>
#include <QTextStream>
#include "mainwindow.h"
#include "okno_dodaj_lokatora.h"


//#include <io.h> // win32
//#else
#include <unistd.h> //unix
//#endif


Operacje_na_plikach::Operacje_na_plikach(QWidget *parent) : QMainWindow(parent)
{
     //sciezka_nazwa_bazy_lokatorow = sciezka_nazwa_pliku_bazy_lokatorow;

}
Operacje_na_plikach::~Operacje_na_plikach()
{

}


bool Operacje_na_plikach::plik_wczytaj()
{
    QFile baza_lokatorow(sciezka_nazwa_bazy_lokatorow);
    if (!baza_lokatorow.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Blad otwarcia pliku do odczyty";
        return false;
    }else
    {
        qDebug() << "Plik otworzony do odczytu";
        while (!baza_lokatorow.atEnd()) {
        QByteArray line = baza_lokatorow.readLine();
        baza_lokatorow.close();
        }
        return true;
    }
}

bool Operacje_na_plikach::dopisz_nowego_lokatora_do_bazy(QString pesel, QString nazwisko,
                                                         QString imie, QString data_meldunku,
                                                         QString internet, QString macc_adres,
                                                         QString dodatkowe_info, QString nazwa_pracodawcy,
                                                         QString nr_pokoju, QString stawka, QString kto_placi,
                                                         QString czy_wplacona_kaucja, QString kaucja_zl,
                                                         QString rozliczenie_miesieczne_dzienne)
{


    QStringList lista_do_zapisu;
    lista_do_zapisu << pesel << imie << nazwisko << data_meldunku << nr_pokoju
                    << rozliczenie_miesieczne_dzienne << stawka << kto_placi << nazwa_pracodawcy
                    << czy_wplacona_kaucja << kaucja_zl << internet << macc_adres << dodatkowe_info;
    QString dane_do_zapisu = lista_do_zapisu.join(";;");
    qDebug() << "Linia do zapisu: " << dane_do_zapisu;
    if(!sprawdz_czy_plik_istnieje(sciezka_nazwa_bazy_lokatorow))
    {
        return false;
    }else
    {
        QFile baza_lokatorow(sciezka_nazwa_bazy_lokatorow);
        if (!baza_lokatorow.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qDebug() << "Zapis do bazy. Blad otwarcia pliku";
            return false;
        }else
        {
//            qDebug() << "Plik otworzony tylko do zapisu.";
            QTextStream plik(&baza_lokatorow);
           // baza_lokatorow.write( reinterpret_cast < char *>( Okno_dodaj_lokatora::dane_meldunkowe ), sizeof( s ));
            plik << dane_do_zapisu << endl;
            baza_lokatorow.close();
//            qDebug() << "Zapis do bazy lokatorów - plik zamknięty";
            return true;
         }
    }
}



void Operacje_na_plikach::pobierz_sciezke_bazy_lokatorow(QString &nowa_sciezka_i_nazwa_bazy_lokatorow)
{
    sciezka_nazwa_bazy_lokatorow = nowa_sciezka_i_nazwa_bazy_lokatorow;
//    qDebug() << "Pobierz ścieżkę do bazy lokatorów. Ustawiona scieżka: " << sciezka_nazwa_bazy_lokatorow;

}

bool Operacje_na_plikach::sprawdz_czy_plik_istnieje(QString &sciezka_nazwa_pliku)
{
    if(QFile::exists(sciezka_nazwa_pliku)){
        return true;
    }else
    {
         qDebug() << "Plik do zapisu nie istnieje. Ścieżka do pliku: " << sciezka_nazwa_pliku;
        return false;
    }
}


QString Operacje_na_plikach::wyszukaj_lokatora(QString parametr_wyszukiwania)
{
    return parametr_wyszukiwania;
}
