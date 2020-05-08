#include "guessnumwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuessNumWidget w;
    w.show();
    return a.exec();
}
