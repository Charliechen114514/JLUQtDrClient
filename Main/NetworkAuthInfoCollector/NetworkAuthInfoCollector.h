#ifndef NETWORKAUTHINFOCOLLECTOR_H
#define NETWORKAUTHINFOCOLLECTOR_H
#include <QString>
#include <QtClassHelperMacros>
#include "ConstParams.h"
class NetworkAuthInfoCollector {
public:
    static constexpr const char* SUMMON_DIR = ParamsConst::_DIR;
    static constexpr const char* SUMMON_FILE_NAME =
        ParamsConst::_MIDDLE_USR_CONFIG;
    Q_DISABLE_COPY(NetworkAuthInfoCollector)
    NetworkAuthInfoCollector() = default;
    std::optional<QString> mac() {
        return _gain_mac_imm();
    }
    QStringList setUserNameAndPasswd(const QString name, const QString passwd);
    std::tuple<QString, QString, QString> metaInfo() const {
        return {userName, passwd, macAddr};
    }
    static bool                     isAuthFileAlreadyExsit();
    static QString                  summon_file_path_name_only();
    static QString                  summon_file_path();
    static std::pair<bool, QString> isConnectingToTargetWifi();

private:
    std::optional<QString> _gain_mac_imm();
    QString                userName;
    QString                passwd;
    QString                macAddr;
};

#endif  // NETWORKAUTHINFOCOLLECTOR_H
