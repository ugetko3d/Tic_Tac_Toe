#include "Tic_Tac_Toe.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tic_Tac_Toe w;
    w.show();
    return a.exec();
}
