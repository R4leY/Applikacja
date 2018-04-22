#include "glowne_okno.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Glowne_Okno w;
    w.show();

    return a.exec();
}
