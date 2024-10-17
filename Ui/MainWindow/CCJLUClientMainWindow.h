#ifndef CCJLUCLIENTMAINWINDOW_H
#define CCJLUCLIENTMAINWINDOW_H
#include <QMainWindow>
#include "CommandExecutor.h"
#include "HelpWindow.h"
#include "JLUClientTrayIcon.h"
#include "NetworkAuthInfoCollector.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class CCJLUClientMainWindow;
}
QT_END_NAMESPACE
class QLabel;
class LoggerWindow;

class CCJLUClientMainWindow : public QMainWindow {
    Q_OBJECT

public:
    CCJLUClientMainWindow(QWidget *parent = nullptr);
    void setMovieState(bool running);
    void loadUi();
    void do_login_or_logout();
    void try_create_user();
    void loadUi(const QString &path);
    void showLoggerWindow();
    ~CCJLUClientMainWindow();
signals:
    void tell_close_dialog();

private slots:
    void handle_output_message(const QString msg);

    // this time situations simple... so, i don't wanna
    // process in one function :(
    void tell_possible_time_out();
    void tell_time_out();
    void tell_auth_failed();
    void handle_connect_success();
    void handle_waitings();
    void minimize_to_hide();
    void quit();
    /* handling the signals of closeEvent */
    void closeEvent(QCloseEvent *closeEvent) override;
    void showAbout();
    void showHelp();

private:
    void login();
    void logout();
    void lazy_init_permanentMessage();
    void lazy_init_logger_window();
    void connections_init();
    void createUser(const QString userName, const QString password);
    void setMovieSource();
    Ui::CCJLUClientMainWindow *ui;
    LoggerWindow              *window;
    NetworkAuthInfoCollector   collector;
    std::shared_ptr<QMovie>    movie_src;
    HelpWindow                *helpWindow{};
    JLUClientTrayIcon          tray_icon_instance{this};
    QLabel                    *__obj_tree_hold_label;
    CommandExecutor           *command_executor = nullptr;
    bool                       is_first_success = false;
    bool                       is_logging       = false;
};
#endif  // CCJLUCLIENTMAINWINDOW_H
