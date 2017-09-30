#include "okno_dodaj_lokatora.h"
#include "ui_okno_dodaj_lokatora.h"
#include <QString>
#include <QDebug>
#include "QDialog"
//#include <QDateTime>
#include "operacje_na_plikach.h"
#include "mainwindow.h"
#include "obsluga_czasu.h"
#include "QMessageBox"
#include "QStyle"

Okno_dodaj_lokatora::Okno_dodaj_lokatora(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Okno_dodaj_lokatora)
{
    ui->setupUi(this);

    sciezka_nazwa_bazy_lokatorow ="";
    dodatkowe_informacje_napis = "Dodatkowe informacje o lokatorze:\n- zalegał z czynszem,\n- był uciążliwy,\n- itp.";
    line_edit_podswietlenie_ostrzegawcze = "QLineEdit {background: yellow;}";
    line_edit_podswietlenie_systemowe = "QLineEdit {background: ;}";
    obsluga_czasu Aktualna_data;
    ui->dateEdit->setDate(Aktualna_data.podaj_aktualna_date());


}

Okno_dodaj_lokatora::~Okno_dodaj_lokatora()
{
    delete ui;
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

}


void Okno_dodaj_lokatora::on_radioButton_Pracodawca_clicked()
{
    ui->lineEdit_Nazwa_pracodawcy->setEnabled(true);
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
           emit Okno_dodaj_lokatora::accept();
    }else
        QMessageBox::information(this, "BŁĄD WPROWADZANIA DANYCH", "Uzupełnij wszystkie pola");

}

void Okno_dodaj_lokatora::on_pushButton_zatwierdz_date_clicked()
{
    ui->pushButton_zatwierdz_date->setDown(true);
    ui->pushButton_zatwierdz_date->setText("Zapisana");
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
       str_poprawnosc_obowiazkowych_danych.id_nazwisko = false;
       ui->lineEdit_Nazwisko->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
       kod_wyjscia = false;

    }else
    {
        str_poprawnosc_obowiazkowych_danych.id_nazwisko = true;
        ui->lineEdit_Nazwisko->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(ui->lineEdit_Imie->text().isEmpty())
    {
        str_poprawnosc_obowiazkowych_danych.id_imie = false;
        ui->lineEdit_Imie->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        str_poprawnosc_obowiazkowych_danych.id_imie = true;
        ui->lineEdit_Imie->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(ui->lineEdit_Nazwa_pracodawcy->text().isEmpty() && ui->radioButton_Pracodawca->isChecked())
    {
       str_poprawnosc_obowiazkowych_danych.id_nazwa_pracodawcy = false;
       ui->lineEdit_Nazwa_pracodawcy->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
       kod_wyjscia = false;
    }else if(ui->radioButton_Pracodawca->isChecked())
    {
        str_poprawnosc_obowiazkowych_danych.id_nazwa_pracodawcy = true;
        ui->lineEdit_Nazwa_pracodawcy->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(ui->lineEdit_Nr_pokoju->text().isEmpty()){
        str_poprawnosc_obowiazkowych_danych.id_nr_pokoju = false;
        ui->lineEdit_Nr_pokoju->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        str_poprawnosc_obowiazkowych_danych.id_nr_pokoju = true;
        ui->lineEdit_Nr_pokoju->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(ui->lineEdit_Stawka->text().isEmpty())
    {
        str_poprawnosc_obowiazkowych_danych.id_stawka = false;
        ui->lineEdit_Stawka->setStyleSheet(line_edit_podswietlenie_ostrzegawcze);
        kod_wyjscia = false;
    }else
    {
        str_poprawnosc_obowiazkowych_danych.id_stawka = true;
        ui->lineEdit_Stawka->setStyleSheet(line_edit_podswietlenie_systemowe);
        if(kod_wyjscia == true) kod_wyjscia = true;
    }

    if(!ui->pushButton_zatwierdz_date->isDown())
    {
     str_poprawnosc_obowiazkowych_danych.id_data_meldunku = false;
     ui->dateEdit->setStyleSheet("QDateEdit {background: yellow}");
    }else
    {
        ui->pushButton_zatwierdz_date->setStyleSheet("QDateEdit { background: ");
    }
    qDebug() << "kod wyjscia sprawdzania danych: " << kod_wyjscia;
    return kod_wyjscia;
}





