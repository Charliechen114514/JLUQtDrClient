#include "AboutInfo.h"
#include <QMessageBox>

QString AboutInfo::AboutInfoFactory::createVersion() {
    return "软件版本: " + QString::number(MAJOR_VERISON) + "." +
           QString::number(MINOR_VERSION) + "\n";
}
QString AboutInfo::AboutInfoFactory::createRepoInfo() {
    return QString("核心软件仓库地址: ") + CORE_REPO_ADDR +
           "\n开发人: " + CORE_AUTHOR + "\n本软件项目地址: " + THIS_REPO_NAME +
           "\n开发人: " + THIS_AUTHOR + "\n";
}

QString AboutInfo::AboutInfoFactory::createInfo() {
    return createVersion() +   // 版本号
           createRepoInfo() +  // 仓库信息
           INFOS;
}

void AboutInfo::showAbout(QWidget *bindings) {
    QMessageBox::about(bindings, AboutInfo::NAME,
                       AboutInfo::AboutInfoFactory::createInfo());
}
