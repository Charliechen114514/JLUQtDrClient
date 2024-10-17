#include "CommandExecutor.h"
#include <QDir>
#include <QMessageBox>

static QString gainCoreExe(const char* FILE_DIR, const char* FILE_NAME) {
    return QDir::cleanPath(QDir::currentPath()) + QDir::separator() + FILE_DIR +
           QDir::separator() + FILE_NAME;
}

CommandExecutor::CommandExecutor(QObject* parent) : QObject(parent) {
    processor = std::make_unique<QProcess>(this);
    connect(processor.get(), &QProcess::readyReadStandardOutput, this,
            &CommandExecutor::handle_output);
}

bool CommandExecutor::owns_main_exe() {
    return QFile::exists(gainCoreExe(FILE_DIR, FILE_NAME));
}

void CommandExecutor::handle_output() {
    emit emitOutputFromConsole(
        QString::fromLocal8Bit(processor->readAllStandardOutput())
            .remove("\033")
            .remove("["));
}
void CommandExecutor::executeCommand(const QStringList& commandParams,
                                     bool               req_wait_for_finish) {
    if (processor->state() == QProcess::Running) {
        QMessageBox::critical(nullptr, "正在执行上一条指令",
                              "正在执行上一条指令，请稍后再试");
        return;
    }
    QString exeFile = gainCoreExe(FILE_DIR, FILE_NAME);
    processor->start(exeFile, commandParams);
    if (!processor->waitForStarted()) {
        QMessageBox::critical(nullptr, "无法启动进程！", "无法启动进程！");
        return;
    }
    if (req_wait_for_finish) processor->waitForFinished();
}

void CommandExecutor::terminate_thread() {
    if (processor->state() != QProcess::Running) return;
    processor->kill();
}

CommandExecutor::~CommandExecutor() {
    if (processor->state() == QProcess::Running) {
        processor->kill();
    }
    // qDebug() << "Process is terminating and will clean!";
    processor->deleteLater();
}
