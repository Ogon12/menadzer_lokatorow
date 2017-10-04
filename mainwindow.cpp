#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "okno_dodaj_lokatora.h"
#include "okno_szukaj_lokatora.h"
#include "operacje_na_plikach.h"

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
//#include <stdlib.h>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sciezka_nazwa_pliku_bazy_lokatorow = "./baza_lokatorow.txt";
    tytul_okna_informacyjengo = "PROBLEM KONFIGURACJI";
    informacje_o_bledzie_dostepu_do_bazy = "Nie odnaleziono bazy danych. \n"
                                           "Sprawdź w ustawieniach poprawność cieżki lub\n"
                                           "ustaw nową bazę informacji.";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Dodaj_lokatora_clicked()
{

    Okno_dodaj_lokatora Dodaj_lokatora;
    Dodaj_lokatora.ustaw_sciezke_i_nazwe_bazy_danych(sciezka_nazwa_pliku_bazy_lokatorow);

    Operacje_na_plikach Sprawdz_plik;
    if(Sprawdz_plik.sprawdz_czy_plik_istnieje(sciezka_nazwa_pliku_bazy_lokatorow))
    {
        Dodaj_lokatora.exec();
    }else
    {

        qDebug() << "plik nie istnieje " << "sciezka: " << sciezka_nazwa_pliku_bazy_lokatorow;
        //system("pwd");
        //qDebug() << "Polecene ls: " << system("ls") << "Polecenie Pwd: " << system("pwd");
        QMessageBox::information(this, tytul_okna_informacyjengo, informacje_o_bledzie_dostepu_do_bazy);
    }
}


void MainWindow::on_pushButton_Szukaj_lokatora_clicked()
{
    Okno_szukaj_lokatora Szukaj_lokatora;
    Szukaj_lokatora.exec();
}

