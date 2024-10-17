#include "LoginChecker.h"
#include <QDir>
#include "ConstParams.h"
#include "NetworkAuthInfoCollector.h"
std::pair<bool, QString> LoginChecker::passCheck() const {
    if (!pass_usr_check()) {
        return {false, "没有用户配置文件！请先创建用户配置文件！"};
    }

    auto network_check = is_using_wifi();
    if (!network_check.first) {
        return {false, network_check.second};
    }

    return {true, "Success"};
}

bool LoginChecker::pass_usr_check() const {
    QDir dir(QDir::currentPath() + QDir::separator() + ParamsConst::_DIR);
    QStringList filters{"*.usr"};
    dir.setNameFilters(filters);
    return dir.count();
}

std::pair<bool, QString> LoginChecker::is_using_wifi() const {
    return NetworkAuthInfoCollector::isConnectingToTargetWifi();
}

std::pair<bool, QStringList> LoginChecker::gain_command_list() const {
    auto check = passCheck();
    if (!check.first) {
        return {false, {check.second}};
    }

    QStringList command_list;
    command_list << "auth" << "-f"
                 << NetworkAuthInfoCollector::summon_file_path();
    return {true, command_list};
}
