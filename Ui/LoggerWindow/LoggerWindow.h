#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QMainWindow>

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
    Ui::LoggerWindow *ui;
};

#endif  // LOGGERWINDOW_H
