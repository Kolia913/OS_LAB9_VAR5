#include "dialog.h"
#include "process.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if(argc == 1) {
        QApplication a(argc, argv);
        Dialog w;
        w.show();
        return a.exec();
    } else {
        QApplication a(argc, argv);
        process w(nullptr, argv[1]);
        w.show();
        return a.exec();
    }
}
