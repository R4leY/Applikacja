#ifndef GLOWNE_OKNO_H
#define GLOWNE_OKNO_H

#include "dodawanie_ucznia.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QBuffer>
#include <QByteArray>
#include <QtEndian>
#include <QSortFilterProxyModel>
namespace Ui {
class Glowne_Okno;
}

class Glowne_Okno : public QMainWindow
{
    Q_OBJECT

public:
    QSortFilterProxyModel *proxyLista;
    explicit Glowne_Okno(QWidget *parent = 0);
    ~Glowne_Okno();


private slots:
    void on_Dodaj_Button_clicked();
    void FillTable();
    void Dodaj(QStringList sl);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Glowne_Okno *ui;
    QTcpSocket *socket;
};

#endif // GLOWNE_OKNO_H
