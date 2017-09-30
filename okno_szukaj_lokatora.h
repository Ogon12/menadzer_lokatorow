#ifndef OKNO_SZUKAJ_LOKATORA_H
#define OKNO_SZUKAJ_LOKATORA_H

#include <QDialog>

namespace Ui {
class Okno_szukaj_lokatora;
}

class Okno_szukaj_lokatora : public QDialog
{
    Q_OBJECT

public:
    explicit Okno_szukaj_lokatora(QWidget *parent = 0);
    ~Okno_szukaj_lokatora();

private:
    Ui::Okno_szukaj_lokatora *ui;
};

#endif // OKNO_SZUKAJ_LOKATORA_H
