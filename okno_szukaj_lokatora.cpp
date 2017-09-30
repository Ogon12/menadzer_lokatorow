#include "okno_szukaj_lokatora.h"
#include "ui_okno_szukaj_lokatora.h"

Okno_szukaj_lokatora::Okno_szukaj_lokatora(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Okno_szukaj_lokatora)
{
    ui->setupUi(this);
}

Okno_szukaj_lokatora::~Okno_szukaj_lokatora()
{
    delete ui;
}
