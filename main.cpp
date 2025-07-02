#include "dialog.h"
#include "dialogstart.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogStart start;
    start.exec();

    if(start.getData() != "")
    {
        Dialog dialog(start.getData());
        dialog.showMaximized();
        return a.exec();
    }


}
