#ifndef JLUCLIENTTRAYICON_H
#define JLUCLIENTTRAYICON_H
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>
#include <QtClassHelperMacros>
class CCJLUClientMainWindow;
class JLUClientTrayIcon : public QObject {
    Q_OBJECT
public:
    JLUClientTrayIcon() = delete;
    JLUClientTrayIcon(CCJLUClientMainWindow* hold);
    ~JLUClientTrayIcon() = default;
    static bool shell_switch_to_icon();
    Q_DISABLE_COPY(JLUClientTrayIcon);
signals:
    void tell_show_up();
    void tell_hide_down();
    void tell_wanna_see_logger();
    void tell_quit();
public slots:
    void emit_show_st();
    void handle_reason(QSystemTrayIcon::ActivationReason reason);

private:
    void                             do_create_instance();
    void                             _installActions();
    void                             _doConnections();
    std::unique_ptr<QSystemTrayIcon> tray_icon_instance;
    std::unique_ptr<QMenu>           menu;
    QAction*                         show_hide_action;
    CCJLUClientMainWindow*           holding_handle;
};

#endif  // JLUCLIENTTRAYICON_H
