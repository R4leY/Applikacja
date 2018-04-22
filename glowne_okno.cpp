#include "glowne_okno.h"
#include "ui_glowne_okno.h"

Glowne_Okno::Glowne_Okno(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Glowne_Okno)
{
    ui->setupUi(this);

    ui->comboBox->clear();
    ui->comboBox->addItem("ID");
    ui->comboBox->addItem("Imię");
    ui->comboBox->addItem("Nazwisko");
    FillTable();
    ui->tableWidget->setSortingEnabled(true);
}

Glowne_Okno::~Glowne_Okno()
{
    delete ui;
}

void Glowne_Okno::on_Dodaj_Button_clicked()
{
    Dodawanie_Ucznia *dodawanie = new Dodawanie_Ucznia(this);
    dodawanie->setModal(true);
    connect(dodawanie, SIGNAL(Dodaj(QStringList)), this, SLOT(Dodaj(QStringList)));
    dodawanie->exec();
}
void Glowne_Okno::FillTable()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("212.87.238.39", 4242);
    if(socket->waitForConnected(300))
    {
      ui->label->setText("Połączono z Serwerem");
      ui->tableWidget->setColumnCount(3);
      ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
      ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Imię"));
      ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Nazwisko"));
      ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
      ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
      ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
      QString query = "querry";
      int myInteger = query.size();
      QByteArray byteArray;
      QBuffer buffer(&byteArray);
      buffer.open(QIODevice::WriteOnly);
      myInteger = qToLittleEndian(myInteger);
      buffer.write((char*)&myInteger, sizeof(qint32));
      socket->write(byteArray);
      socket->write(query.toLocal8Bit());
      socket->flush();
      socket->waitForReadyRead(300);
      QByteArray package = socket->read(4);
      int i = qFromLittleEndian<quint64>((const uchar*)package.constData());
      socket->waitForReadyRead(300);
      QByteArray work_array;
      if(socket->bytesAvailable() == 0)
      {
          qDebug()<<"Nothing to see";
      }
      else
      {
      while( i > work_array.size())
      {
       work_array.append(socket->readAll());
      }
      }
      QString work_string(work_array);
      QStringList resultStrings = work_string.split('\n');
      int size = resultStrings.size()-1;
      ui->tableWidget->setRowCount(size);
      int s = 0;
      while(s < resultStrings.size()-1)
      {
          QString ChangeString(resultStrings[s]);
          QStringList FinalStringList = ChangeString.split(";");
          QString ID = FinalStringList[0];
          QTableWidgetItem *item = new QTableWidgetItem();
          int myNumber = ID.toInt();
          item->setData(Qt::DisplayRole, myNumber);
          ui->tableWidget->setItem(s, 0, item);
          QString imie = FinalStringList[1];
          QTableWidgetItem *item2=new QTableWidgetItem (imie);
          ui->tableWidget->setItem(s,1,item2);
          QString Nazwisko = FinalStringList[2];
          QTableWidgetItem *item3=new QTableWidgetItem (tr(Nazwisko.toUtf8()));
          ui->tableWidget->setItem(s,2,item3);
          s++;
      }
    }
    else
    {
        ui->label->setText("Nie Połączono z Serwerem");
    }
}
void Glowne_Okno::Dodaj(QStringList sl)
{
    QString dodaj = "add;"+sl[0]+";"+sl[1];
    int myInteger = dodaj.size();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    myInteger = qToLittleEndian(myInteger);
    buffer.write((char*)&myInteger, sizeof(qint32));
    socket->write(byteArray);
    socket->write(dodaj.toLocal8Bit());
    socket->flush();
    FillTable();
}
void Glowne_Okno::on_lineEdit_textChanged(const QString &arg1)
{
    int index = ui->comboBox->currentIndex();
    int rows = ui->tableWidget->rowCount();
    for(int i = 0; i < rows; ++i)
    {
        if(ui->tableWidget->item(i, index)->text().contains(arg1))
        {
            ui->tableWidget->showRow(i);
        }
         else
        {
           ui->tableWidget->hideRow(i);
        }
    }
    if(arg1.isEmpty())
    {
    for(int i = 0 ; i<rows ; i++)
    {
      ui->tableWidget->showRow(i);
    }
    }
}
