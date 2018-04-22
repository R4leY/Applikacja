#include "dodawanie_ucznia.h"
#include "ui_dodawanie_ucznia.h"
#include "glowne_okno.h"
Dodawanie_Ucznia::Dodawanie_Ucznia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodawanie_Ucznia)
{
    ui->setupUi(this);
    QDialog::setWindowFlags(QDialog::windowFlags()&~Qt::WindowContextHelpButtonHint);
}
Dodawanie_Ucznia::~Dodawanie_Ucznia()
{
    delete ui;
}

void Dodawanie_Ucznia::on_Dodaj_Button_1_clicked()
{
    if(ui->Imie_Edit->text().isEmpty() || ui->nazwisko_edit->text().isEmpty())
    {
     QMessageBox::critical(this,"Error","Wypełnij wymagane pola");
    }
    else
    {
    QStringList data;
    data.append(ui->Imie_Edit->text());
    data.append(ui->nazwisko_edit->text());
    emit Dodaj(data);
    this->hide();
    }
}
