#include "HelpInfo.h"
#include <QFile>

QString HelpInfo::gainHelpMarkDown(const char* path) {
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    if (f.isOpen()) {
        return f.readAll();
    }
    return "";
}
