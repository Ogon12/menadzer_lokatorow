#include "okno_dodaj_lokatora.h"
#include "ui_okno_dodaj_lokatora.h"
#include <QString>
#include <QDebug>
#include "QDialog"
#include <QDateTime>
#include "operacje_na_plikach.h"
#include "mainwindow.h"
#include "obsluga_czasu.h"
#include "QMessageBox"
#include "QStyle"
#include <QCheckBox>
#include <QDoubleValidator>
#include "QValidator"



Okno_dodaj_lokatora::Okno_dodaj_lokatora(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Okno_dodaj_lokatora)
{
    ui->setupUi(this);

    sciezka_nazwa_bazy_lokatorow ="";
    miesiecznie = "miesięcznie";
    dzienne = "dzienne";
    brak = "brak";
    tak = "tak";

    dodatkowe_informacje_napis = "Dodatkowe informacje o lokatorze:\n- zalegał z czynszem,\n- był uciążliwy,\n- itp.";
    line_edit_podswietlenie_ostrzegawcze = "QLineEdit {background: yellow;}";
    line_edit_podswietlenie_systemowe = "QLineEdit {background: ;}";
    obsluga_czasu Aktualna_data;
    ui->dateEdit->setDate(Aktualna_data.podaj_aktualna_date());
    ui->lineEdit_Stawka->setValidator( new QDoubleValidator(0, 2000, 2, this) ); //wprowadza liczby z przecinkiem
    wsk_dane_meldunkowe = new dane_meldunkowe;
    wsk_poprawnosc_obowiazkowych_danych = new poprawnosc_obowiazkowych_danych;
}

Okno_dodaj_lokatora::~Okno_dodaj_lokatora()
{
    delete ui;
    delete wsk_dane_meldunkowe;
    delete wsk_poprawnosc_obowiazkowych_danych;
}


//ogługa wyjdz - Anuluj
void Okno_dodaj_lokatora::on_pushButton_Anuluj_clicked()
{
    emit Okno_dodaj_lokatora::reject();
}


void Okno_dodaj_lokatora::on_checkBox_dodatkow_informacje_clicked()
{
    if(ui->checkBox_dodatkow_informacje->isChecked())
    {
        ui->plainTextEdit_Uwagi_o_lokatorze->clear();
    }else
    {
        ui->plainTextEdit_Uwagi_o_lokatorze->setPlainText(dodatkowe_informacje_napis);
    }
}



void Okno_dodaj_lokatora::on_radioButton_Prywatnie_clicked()
{
    ui->lineEdit_Nazwa_pracodawcy->setText("Kto rozlicza");
    ui->lineEdit_Nazwa_pracodawcy->setEnabled(false);
    ui->lineEdit_Nazwa_pracodawcy->setStyleSheet("QlineEdit {baclground: ;}");
    ui->label_kto_rozlicza_gwiazda->setEnabled(false);

}


void Okno_dodaj_lokatora::on_radioButton_Pracodawca_clicked()
{
    ui->lineEdit_Nazwa_pracodawcy->setEnabled(true);
    ui->label_kto_rozlicza_gwiazda->setEnabled(true);
}


void Okno_dodaj_lokatora::on_radioButton_Stawk_dzienna_released()
{
    ui->label_waluta->setText("zł/dn");
}


void Okno_dodaj_lokatora::on_radioButton_Stawka_miesieczna_released()
{
    ui->label_waluta->setText("zł/mc");
}


void Okno_dodaj_lokatora::on_pushButton_wyjdz_zapisz_clicked()
{
    if(sprawdz_poprawnosc_danych())
    {
        zapisz_dane_do_struktury();

        Operacje_na_plikach oper_plikowe;
        oper_plikowe.pobierz_sciezke_bazy_lokatorow(sciezka_nazwa_bazy_lokatorow);

        if(oper_plikowe.dopisz_nowego_lokatora_do_bazy(wsk_dane_meldunkowe->pesel, wsk_dane_meldunkowe->nazwisko, wsk_dane_meldunkowe->imie,
                                                       wsk_dane_meldunkowe->data_meldunku, wsk_dane_meldunkowe->internet,
                                                       wsk_dane_meldunkowe->macc_adres, wsk_dane_meldunkowe->dodatkowe_info,
                                                       wsk_dane_meldunkowe->nazwa_pracodawcy, wsk_dane_meldunkowe->nr_pokoju,
                                                       wsk_dane_meldunkowe->stawka, wsk_dane_meldunkowe->kto_plci,
                                                       wsk_dane_meldunkowe->czy_wplacona_kaucja, wsk_dane_meldunkowe->kaucja_zl,
                                                       wsk_dane_meldunkowe->rozliczenie_miesieczne_dzienne))
        {
            emit Okno_dodaj_lokatora::accept();
        }else
        {
            qDebug() << "Błąd zapisu do pliku";
            QMessageBox::critical(this, "BŁĄD ZAPISU DANYCH", "Sprawdz czy:\n"
                                                              "- plik bazy danych istnieie,\n"
                                                              "- masz prawa dostępu i zapisu do pliku bazy danych,\n"
                                                              "- plik bazy danych jest używany przez inną aplikacje.");
        }
    }else
        QMessageBox::information(this, "BŁĄD WPROWADZANIA DANYCH", "Uzupełnij wszystkie pola");
}


void Okno_dodaj_lokatora::ustaw_sciezke_i_nazwe_bazy_danych(QString &nowa_sciezka_i_nazwa_bazy_danych)
{
    sciezka_nazwa_bazy_lokatorow = nowa_sciezka_i_nazwa_bazy_danych;
}

bool Okno_dodaj_lokatora::sprawdz_poprawnosc_danych()
{
    bool kod_wyjscia = true;

    if(ui->lineEdit_Nazwisko->text().isEmpty())
    {
       wsk_poprawnosc_obowiazkowych_danych->id_nazwisko = false;
       ui->lineEdit_Nazwisko->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
       kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_nazwisko = true;
        ui->lineEdit_Nazwisko->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->lineEdit_Imie->text().isEmpty())
    {
        wsk_poprawnosc_obowiazkowych_danych->id_imie = false;
        ui->lineEdit_Imie->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_imie = true;
        ui->lineEdit_Imie->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->lineEdit_Nazwa_pracodawcy->text().isEmpty() && ui->radioButton_Pracodawca->isChecked())
    {
       wsk_poprawnosc_obowiazkowych_danych->id_nazwa_pracodawcy = false;
       ui->lineEdit_Nazwa_pracodawcy->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
       kod_wyjscia = false;
    }else if(ui->radioButton_Pracodawca->isChecked())
    {
        wsk_poprawnosc_obowiazkowych_danych->id_nazwa_pracodawcy = true;
        ui->lineEdit_Nazwa_pracodawcy->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->lineEdit_Nr_pokoju->text().isEmpty()){
        wsk_poprawnosc_obowiazkowych_danych->id_nr_pokoju = false;
        ui->lineEdit_Nr_pokoju->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_nr_pokoju = true;
        ui->lineEdit_Nr_pokoju->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(ui->lineEdit_Stawka->text().isEmpty())
    {
        wsk_poprawnosc_obowiazkowych_danych->id_stawka = false;
        ui->lineEdit_Stawka->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_stawka = true;
        ui->lineEdit_Stawka->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->lineEdit_zatwierdzona_data->text().isEmpty())
    {
        wsk_poprawnosc_obowiazkowych_danych->id_data_meldunku = false;
        ui->lineEdit_zatwierdzona_data->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
         kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_data_meldunku = true;
        ui->lineEdit_zatwierdzona_data->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->checkBox_kaucja->isChecked() && ui->lineEdit_kaucja_pln->text().isEmpty())
    {
       wsk_poprawnosc_obowiazkowych_danych->id_kaucja_zl = false;
       ui->lineEdit_kaucja_pln->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
       kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_kaucja_zl = true;
        ui->lineEdit_kaucja_pln->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }


    if(ui->lineEdit_pesel->text().isEmpty()){
        wsk_poprawnosc_obowiazkowych_danych->id_pesel = false;
        ui->lineEdit_pesel->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        wsk_poprawnosc_obowiazkowych_danych->id_pesel = false;
        ui->lineEdit_pesel->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }
    qDebug() << "kod wyjscia sprawdzania danych: " << kod_wyjscia;
    return kod_wyjscia;
}

void Okno_dodaj_lokatora::zapisz_dane_do_struktury()
{
    wsk_dane_meldunkowe->imie = ui->lineEdit_Imie->text();
    wsk_dane_meldunkowe->nazwisko = ui->lineEdit_Nazwisko->text();
    wsk_dane_meldunkowe->nr_pokoju = ui->lineEdit_Nr_pokoju->text();
    wsk_dane_meldunkowe->data_meldunku = ui->dateEdit->text();
    wsk_dane_meldunkowe->pesel = ui->lineEdit_pesel->text();
    wsk_dane_meldunkowe->stawka = ui->lineEdit_Stawka->text();

    if(ui->checkBox_Internet->isChecked())
    {
        wsk_dane_meldunkowe->macc_adres = ui->lineEdit_MAC_ADDRES->text();
        wsk_dane_meldunkowe->internet = tak;
    }else
    {
        wsk_dane_meldunkowe->internet = brak;
        wsk_dane_meldunkowe->macc_adres = brak;
    }

    if(ui->radioButton_Stawk_dzienna->isChecked())
    {
        wsk_dane_meldunkowe->rozliczenie_miesieczne_dzienne = dzienne;
    }else
    {
        wsk_dane_meldunkowe->rozliczenie_miesieczne_dzienne = miesiecznie;
    }

    if(ui->checkBox_dodatkow_informacje->isChecked()){
        wsk_dane_meldunkowe->dodatkowe_info = ui->plainTextEdit_Uwagi_o_lokatorze->toPlainText();
    }else
    {
        wsk_dane_meldunkowe->dodatkowe_info = brak;
    }

    if(ui->checkBox_kaucja->isChecked()){
        wsk_dane_meldunkowe->czy_wplacona_kaucja = tak;
        wsk_dane_meldunkowe->kaucja_zl = ui->lineEdit_kaucja_pln->text();
    }else{
        wsk_dane_meldunkowe->czy_wplacona_kaucja = brak;
        wsk_dane_meldunkowe->kaucja_zl = brak;
    }

    if(ui->radioButton_Pracodawca->isChecked())
    {
        wsk_dane_meldunkowe->nazwa_pracodawcy = ui->lineEdit_Nazwa_pracodawcy->text();
        wsk_dane_meldunkowe->kto_plci = "pracodawca";
    }else
    {
        wsk_dane_meldunkowe->nazwa_pracodawcy = "Zameldowany";
        wsk_dane_meldunkowe->kto_plci = "prywatnie";
    }
}


void Okno_dodaj_lokatora::on_pushButton_wyczysc_zapisana_date_clicked()
{
    ui->pushButton_zatwierdz_date->setText("Zatwierdź*");
    ui->pushButton_zatwierdz_date->setDown(false);
}

void Okno_dodaj_lokatora::on_pushButton_zatwierdz_date_clicked()
{
    ui->pushButton_zatwierdz_date->setText("Zapisana");
    ui->lineEdit_zatwierdzona_data->setText(ui->dateEdit->text());
}


void Okno_dodaj_lokatora::on_checkBox_kaucja_clicked()
{
    if(!ui->checkBox_kaucja->isChecked())
    {
        ui->lineEdit_kaucja_pln->setStyleSheet(line_edit_podswietlenie_systemowe);
    }
}



