#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_okno_dodaj_lokatora.h"
#include "okno_dodaj_lokatora.h"
#include "okno_szukaj_lokatora.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString sciezka_nazwa_pliku_bazy_lokatorow;
    QString informacje_o_bledzie_dostepu_do_bazy;
    QString tytul_okna_informacyjengo;


private slots:
    void on_pushButton_Dodaj_lokatora_clicked();

    void on_pushButton_Szukaj_lokatora_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
