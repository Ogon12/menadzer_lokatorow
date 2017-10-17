#ifndef OKNO_DODAJ_LOKATORA_H
#define OKNO_DODAJ_LOKATORA_H
#include <QDialog>
#include <QString>
#include <operacje_na_plikach.h>


#include "mainwindow.h"

namespace Ui {
class Okno_dodaj_lokatora;
}

class Okno_dodaj_lokatora : public QDialog
{
    Q_OBJECT


public:
    explicit Okno_dodaj_lokatora(QWidget *parent = 0);
    ~Okno_dodaj_lokatora();
private:
    QString sciezka_nazwa_bazy_lokatorow;
    QString dodatkowe_informacje_napis;
    QString line_edit_podswietlenie_ostrzegawcze;
    QString line_edit_podswietlenie_systemowe;
    QString brak;
    QString miesiecznie;
    QString dzienne;
    QString tak;
public:
    struct dane_meldunkowe
    {
      QString pesel;
      QString nazwisko;
      QString imie;
      QString data_meldunku;
      QString internet;
      QString macc_adres;
      QString dodatkowe_info;
      QString nazwa_pracodawcy;
      QString nr_pokoju;
      QString stawka;
      QString kto_plci;
      QString czy_wplacona_kaucja;
      QString kaucja_zl;
      QString rozliczenie_miesieczne_dzienne;
    } *wsk_dane_meldunkowe;

    struct poprawnosc_obowiazkowych_danych
    {
        bool id_pesel;
        bool id_nazwisko;
        bool id_imie;  
        bool id_data_meldunku;
        bool id_internet;
        bool id_mac_add;
        bool id_dodatkowe_info;
        bool id_nr_pokoju;
        bool id_stawka;
        bool id_kto_placi;
        bool id_nazwa_pracodawcy;
        bool id_czy_placil_kaucje;
        bool id_kaucja_zl;
    } *wsk_poprawnosc_obowiazkowych_danych;

private slots:

    void on_pushButton_Anuluj_clicked();

    void on_pushButton_wyjdz_zapisz_clicked();

    void on_radioButton_Stawk_dzienna_released();

    void on_radioButton_Stawka_miesieczna_released();

    void on_checkBox_dodatkow_informacje_clicked();

    void on_radioButton_Prywatnie_clicked();

    void on_radioButton_Pracodawca_clicked();

    void on_pushButton_zatwierdz_date_clicked();

    void on_pushButton_wyczysc_zapisana_date_clicked();

    void on_checkBox_kaucja_clicked();


private:
    Ui::Okno_dodaj_lokatora *ui;


public:
    void ustaw_sciezke_i_nazwe_bazy_danych(QString &nowa_sciezka_i_nazwa_bazy_danych);
    bool sprawdz_poprawnosc_danych();
    void zapisz_dane_do_struktury();
};

#endif // OKNO_DODAJ_LOKATORA_H
