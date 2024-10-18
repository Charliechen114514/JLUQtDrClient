#include "LoggerWindow.h"
#include <QMessageBox>
#include "StateChecker.h"
#include "ui_LoggerWindow.h"
LoggerWindow::LoggerWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoggerWindow) {
    ui->setupUi(this);
    ui->textBrowser_output->setFont(QFont("Consola", 14));
}

void LoggerWindow::append_output(const QString& message) {
    auto res = StateChecker::gain_state_info(message);

    switch (res) {
        case StateChecker::ErrorCode::NO_ERROR:
            emit connect_success();
            break;
        case StateChecker::ErrorCode::AUTH_FAILED:
            emit authentic_failed();
            break;
        case StateChecker::ErrorCode::POSSIBLE_TIME_OUT:
            emit may_no_connections();
            break;
        case StateChecker::ErrorCode::TIME_OUT:
            emit no_connection();
            break;
        case StateChecker::ErrorCode::WAITING:
            emit awaiting_connections();
            break;
    }

#ifdef CLEAR_LOG_IF_REACH_LIMITATION
    // Clear the logger for no more message...
    if (check_shell_clear(ui->textBrowser_output->toPlainText())) {
        ui->textBrowser_output->clear();
    }
#endif
    ui->textBrowser_output->append(message);
}

QString LoggerWindow::outputCurrent() const {
    return ui->textBrowser_output->toPlainText();
}

LoggerWindow::~LoggerWindow() {
    delete ui;
}
