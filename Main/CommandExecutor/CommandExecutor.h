#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <QObject>
#include <QProcess>
#include <QtClassHelperMacros>
#include "ConstParams.h"
class CommandExecutor : public QObject {
    Q_OBJECT
public:
    CommandExecutor(QObject* parent = nullptr);
    ~CommandExecutor();
    Q_DISABLE_COPY(CommandExecutor);

    void        executeCommand(const QStringList& commandParams,
                               bool               req_wait_for_finish = false);
    void        terminate_thread();
    static bool owns_main_exe();
signals:
    void emitOutputFromConsole(const QString msg_append);
    void finishCode(const int code);
    void thread_start();
    void thread_end();
private slots:
    void handle_output();

private:
    static constexpr const char* FILE_NAME = ParamsConst::_FILE;
    static constexpr const char* FILE_DIR  = ParamsConst::_DIR;
    std::unique_ptr<QProcess>    processor;
};

#endif  // COMMANDEXECUTOR_H
