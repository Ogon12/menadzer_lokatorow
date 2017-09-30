#ifndef OPERACJE_NA_PLIKACH_H
#define OPERACJE_NA_PLIKACH_H

#include <QMainWindow>
#include <QString>


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
    bool sprawdz_czy_plik_istnieje(QString sciezka_nazwa_pliku);
    bool plik_wczytaj();
    bool dopisz_nowego_lokatora(QString dane);
    QString wyszukaj_lokatora(QString parametr_wyszukiwania);
};

#endif // OPERACJE_NA_PLIKACH_H
