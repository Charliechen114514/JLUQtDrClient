#include <QApplication>
#include "CCJLUClientMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    CCJLUClientMainWindow w;
    w.show();
    return a.exec();
}
