#ifndef LOGINCHECKER_H
#define LOGINCHECKER_H
#include <QString>
#include <QtClassHelperMacros>
class LoginChecker {
public:
    LoginChecker() = default;
    Q_DISABLE_COPY(LoginChecker);
    std::pair<bool, QString>     passCheck() const;
    std::pair<bool, QStringList> gain_command_list() const;

private:
    bool                     pass_usr_check() const;
    std::pair<bool, QString> is_using_wifi() const;
};

#endif  // LOGINCHECKER_H
