#ifndef OPERACJE_NA_PLIKACH_H
#define OPERACJE_NA_PLIKACH_H

#include <QMainWindow>
#include <QString>
#include "okno_dodaj_lokatora.h"



class Operacje_na_plikach : public QMainWindow
{
    Q_OBJECT
public:
    explicit Operacje_na_plikach(QWidget *parent = 0);

    ~Operacje_na_plikach();
signals:


public slots:


public:
    QString sciezka_nazwa_bazy_lokatorow;



public:
    void pobierz_sciezke_bazy_lokatorow(QString &sciezka_i_nazwa_bazy_lokatorow);
    bool sprawdz_czy_plik_istnieje(QString &sciezka_nazwa_pliku);
    bool plik_wczytaj();
    bool dopisz_nowego_lokatora_do_bazy(QString pesel, QString nazwisko,
                                        QString imie, QString data_meldunku,
                                        QString internet, QString macc_adres,
                                        QString dodatkowe_info, QString nazwa_pracodawcy,
                                        QString nr_pokoju, QString stawka, QString kto_placi,
                                        QString czy_wplacona_kaucja, QString kaucja_zl,
                                        QString rozliczenie_miesieczne_dzienne);

    QString wyszukaj_lokatora(QString parametr_wyszukiwania);
};

#endif // OPERACJE_NA_PLIKACH_H
