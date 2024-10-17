#include "NetworkAuthInfoCollector.h"
#include <QDir>
#include <QNetworkInformation>
#include <QNetworkInterface>

static QString gainCoreFile(const char* FILE_DIR, const char* FILE_NAME) {
    return QDir::cleanPath(QDir::currentPath()) + QDir::separator() + FILE_DIR +
           QDir::separator() + FILE_NAME;
}

struct NetWorkUtils {
    static bool _isWifiMac(const QNetworkInterface& interface) {
        return interface.flags().testFlag(QNetworkInterface::IsUp) &&
               interface.flags().testFlag(QNetworkInterface::IsLoopBack) ==
                   false &&
               interface.type() == QNetworkInterface::Wifi;
    }

    static bool auth_file_exsits() {
        return QFile::exists(
            gainCoreFile(NetworkAuthInfoCollector::SUMMON_DIR,
                         NetworkAuthInfoCollector::SUMMON_FILE_NAME));
    }
};

QString NetworkAuthInfoCollector::summon_file_path() {
    return gainCoreFile(SUMMON_DIR, SUMMON_FILE_NAME);
}

QString NetworkAuthInfoCollector::summon_file_path_name_only() {
    return SUMMON_FILE_NAME;
}

bool NetworkAuthInfoCollector::isAuthFileAlreadyExsit() {
    return NetWorkUtils::auth_file_exsits();
}

QStringList NetworkAuthInfoCollector::setUserNameAndPasswd(
    const QString name, const QString passwd) {
    QStringList args;
    auto        mac = _gain_mac_imm();
    if (!mac.has_value()) {
        return {};
    }
    this->passwd   = passwd;
    this->userName = name;
    this->macAddr  = mac.value();
    args << "user" << "create"
         << "-u" << this->userName << "-p" << this->passwd << "-m"
         << this->macAddr << "-f" << summon_file_path();
    return args;
}

std::optional<QString> NetworkAuthInfoCollector::_gain_mac_imm() {
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, interfaces) {
        // 判断该网卡是否为有效的网络接口
        if (NetWorkUtils::_isWifiMac(interface)) {
            // 获取该网卡的硬件地址（即MAC地址）
            return {interface.hardwareAddress().toUpper()};
        }
    }
    return {};
}

std::pair<bool, QString> NetworkAuthInfoCollector::isConnectingToTargetWifi() {
    // check if is in online
    auto names = QNetworkInformation::availableBackends();
    if (names.empty()) {
        return {false, "无可用的网络管理器 :("};
    }
    QNetworkInformation::loadBackendByName(names[0]);
    auto instance = QNetworkInformation::instance();

    if (instance->transportMedium() !=
        QNetworkInformation::TransportMedium::WiFi) {
        // qDebug() << "Not online";
        return {"false", "请检查自己连接的是无线网！"};
    }

    // qDebug() << instance->backendName();

    return {true, "检查通过！"};
}
