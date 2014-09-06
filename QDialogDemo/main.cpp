#include "finddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindDialog* dialog = new FindDialog;
    dialog->show();
    return a.exec();
}
