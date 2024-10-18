#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QMainWindow>
#include "ConstParams.h"

namespace Ui {
class LoggerWindow;
}

class LoggerWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoggerWindow(QWidget *parent = nullptr);
    void    append_output(const QString &message);
    QString outputCurrent() const;
    ~LoggerWindow();
signals:
    void authentic_failed();
    void may_no_connections();
    void no_connection();
    void connect_success();
    void awaiting_connections();

private:
#ifdef CLEAR_LOG_IF_REACH_LIMITATION
    bool inline check_shell_clear(const QString &checkee) {
        return checkee.size() >= ParamsConst::MAX_ALLOWED_BUFFER_FOR_CLEAR;
    }
#endif
    Ui::LoggerWindow *ui;
};

#endif  // LOGGERWINDOW_H
