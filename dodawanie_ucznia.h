#ifndef DODAWANIE_UCZNIA_H
#define DODAWANIE_UCZNIA_H

#include <QDialog>
#include <QMessageBox>
#include "glowne_okno.h"

namespace Ui {
class Dodawanie_Ucznia;
}

class Dodawanie_Ucznia : public QDialog
{
    Q_OBJECT

public:
    explicit Dodawanie_Ucznia(QWidget *parent = 0);
    ~Dodawanie_Ucznia();
private slots:
    void on_Dodaj_Button_1_clicked();

signals:
        void Dodaj(QStringList sl);
private:
    Ui::Dodawanie_Ucznia *ui;
};

#endif // DODAWANIE_UCZNIA_H
