#include "JLUClientTrayIcon.h"
#include <QMessageBox>
#include "CCJLUClientMainWindow.h"
bool JLUClientTrayIcon::shell_switch_to_icon() {
    QMessageBox box;
    box.setIcon(QMessageBox::Icon::Information);
    box.setWindowTitle("是否退出?");
    box.setText("是否需要隐藏到托盘?");
    box.addButton("最小化到托盘", QMessageBox::ButtonRole::YesRole);
    box.addButton("退出程序", QMessageBox::ButtonRole::NoRole);
    box.exec();
    auto reply = box.result();
    return reply == 0;
}

void JLUClientTrayIcon::emit_show_st() {
    if (holding_handle->isHidden()) {
        show_hide_action->setText("隐藏窗口");
        emit tell_show_up();
    } else {
        show_hide_action->setText("显示窗口");
        emit tell_hide_down();
    }
}

JLUClientTrayIcon::JLUClientTrayIcon(CCJLUClientMainWindow* holding) {
    holding_handle = holding;
    do_create_instance();
    _doConnections();
}

void JLUClientTrayIcon::do_create_instance() {
    tray_icon_instance = std::make_unique<QSystemTrayIcon>(this);
    tray_icon_instance->setIcon(QIcon(":/ico/ccjluclient.ico"));
    _installActions();
    tray_icon_instance->setToolTip("CCJLUDrClient");
    tray_icon_instance->show();
}

void JLUClientTrayIcon::_installActions() {
    menu = std::make_unique<QMenu>();
    // install the showup/show down actions
    QAction* show_event_action = new QAction("", menu.get());
    connect(show_event_action, &QAction::triggered, this,
            &JLUClientTrayIcon::emit_show_st);
    show_event_action->setText("隐藏窗口");
    menu->addAction(show_event_action);
    show_hide_action = show_event_action;

    // install the view logger action
    QAction* view_logger = new QAction("查看日志", menu.get());
    connect(view_logger, &QAction::triggered, this,
            &JLUClientTrayIcon::tell_wanna_see_logger);
    menu->addAction(view_logger);

    // install the quit_action
    QAction* quit_action = new QAction("退出", menu.get());
    connect(quit_action, &QAction::triggered, this,
            &JLUClientTrayIcon::tell_quit);
    menu->addAction(quit_action);
    tray_icon_instance->setContextMenu(menu.get());
}

void JLUClientTrayIcon::_doConnections() {
    connect(this, &JLUClientTrayIcon::tell_hide_down, holding_handle,
            &CCJLUClientMainWindow::hide);
    connect(this, &JLUClientTrayIcon::tell_show_up, holding_handle,
            &CCJLUClientMainWindow::show);
    connect(this, &JLUClientTrayIcon::tell_quit, holding_handle,
            &CCJLUClientMainWindow::close);
    connect(this, &JLUClientTrayIcon::tell_wanna_see_logger, holding_handle,
            &CCJLUClientMainWindow::showLoggerWindow);
    connect(tray_icon_instance.get(), &QSystemTrayIcon::activated, this,
            &JLUClientTrayIcon::handle_reason);
}

void JLUClientTrayIcon::handle_reason(
    QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::DoubleClick:
            emit tell_show_up();
            break;
        case QSystemTrayIcon::Unknown:
        case QSystemTrayIcon::Context:
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::MiddleClick:
            break;
    }
}
