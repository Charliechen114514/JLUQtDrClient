#include "CCJLUClientMainWindow.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QMovie>
#include "CommandExecutor.h"
#include "ConstParams.h"
#include "Info/help/HelpInfo.h"
#include "LoggerWindow.h"
#include "LoginChecker.h"
#include "NetworkAuthInfoCollector.h"
#include "UiLoader.h"
#include "UserCreatorDialog.h"
#include "ui_CCJLUClientMainWindow.h"

/*
    主构造函数：负责完成程序启动的加载工作：
        加载UI
        分配对应控件的内存
        初始化生成器 <- 对象树维护
        加载对象信号与槽
        加载gif小动画
*/

CCJLUClientMainWindow::CCJLUClientMainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CCJLUClientMainWindow) {
    ui->setupUi(this);
    loadUi();
    lazy_init_permanentMessage();
    lazy_init_logger_window();
    command_executor = new CommandExecutor(this);
    connections_init();
    setMovieSource();
}

void CCJLUClientMainWindow::connections_init() {
    connect(command_executor, &CommandExecutor::emitOutputFromConsole, this,
            &CCJLUClientMainWindow::handle_output_message);

    connect(ui->action_check_logger, &QAction::triggered, this,
            &CCJLUClientMainWindow::showLoggerWindow);
    connect(ui->action_create_user, &QAction::triggered, this,
            &CCJLUClientMainWindow::try_create_user);
    connect(ui->action_login, &QAction::triggered, this,
            &CCJLUClientMainWindow::do_login_or_logout);
    connect(ui->action_mini, &QAction::triggered, this,
            &CCJLUClientMainWindow::minimize_to_hide);
    connect(ui->action_about, &QAction::triggered, this,
            &CCJLUClientMainWindow::showAbout);
    connect(ui->action_helpWindow, &QAction::triggered, this,
            &CCJLUClientMainWindow::showHelp);

    connect(ui->action_quit, &QAction::triggered, this,
            &CCJLUClientMainWindow::quit);

    connect(ui->btn_login, &QPushButton::clicked, this,
            &CCJLUClientMainWindow::do_login_or_logout);

    connect(this->window, &LoggerWindow::may_no_connections, this,
            &CCJLUClientMainWindow::tell_possible_time_out);
    connect(this->window, &LoggerWindow::no_connection, this,
            &CCJLUClientMainWindow::tell_time_out);
    connect(this->window, &LoggerWindow::authentic_failed, this,
            &CCJLUClientMainWindow::tell_auth_failed);
    connect(this->window, &LoggerWindow::connect_success, this,
            &CCJLUClientMainWindow::handle_connect_success);
    connect(this->window, &LoggerWindow::awaiting_connections, this,
            &CCJLUClientMainWindow::handle_waitings);
}

void CCJLUClientMainWindow::setMovieSource() {
    movie_src = std::make_shared<QMovie>(":/movies/running.gif");
    ui->label_show_state->setMovie(movie_src.get());
    movie_src->start();
    movie_src->stop();
}

/*
    右下角状态栏
*/

void CCJLUClientMainWindow::lazy_init_permanentMessage() {
    __obj_tree_hold_label = new QLabel(this);
    __obj_tree_hold_label->setWordWrap(true);
    statusBar()->addPermanentWidget(__obj_tree_hold_label);
}

/*

    分配日志窗口

*/

void CCJLUClientMainWindow::lazy_init_logger_window() {
    window = new LoggerWindow(this);
}

/*

    加载主窗口Ui

*/

void CCJLUClientMainWindow::loadUi() {
    QString default_path = ParamsConst::UiLoaderQSS;
    loadUi(default_path);
    setFixedSize(QSize(1024 / 3, 768 / 2));
}

/*
    实际的方法函数：目前没有开放自定义设置QSS！
*/

void CCJLUClientMainWindow::loadUi(const QString& path) {
    UiLoader loader;
    auto     qss = loader.fromUiFile(path);
    if (!qss.has_value()) {
        QMessageBox::warning(this, "出现异常",
                             "无法正确加载qss文件" + loader.errorString());
        return;
    }
    setStyleSheet(qss.value());
}

/*
    创建用户的Impl函数，实际上完成的就是接受得到的信息完成创建
*/

void CCJLUClientMainWindow::createUser(const QString userName,
                                       const QString password) {
    auto command_line = collector.setUserNameAndPasswd(userName, password);
    command_executor->executeCommand(command_line, true);
    emit tell_close_dialog();
}

/*
    创建用户的Interface函数，执行的最外逻辑函数
*/

void CCJLUClientMainWindow::try_create_user() {
    if (!CommandExecutor::owns_main_exe()) {
        QMessageBox::critical(this, "映像丢失！",
                              "请下载驱动程序！具体参考帮助文档指引！");
        showHelp();
        return;
    }

    if (is_logging) {
        QMessageBox::critical(this, "错误",
                              "请先取消登录，删除旧的配置文件后再创建用户！");
        return;
    }

    if (NetworkAuthInfoCollector::isAuthFileAlreadyExsit()) {
        QMessageBox::critical(this, "错误", "请删除旧配置文件！");
        return;
    }
    UserCreatorDialog dialog(this, this);
    connect(&dialog, &UserCreatorDialog::tellUserInfo, this,
            &CCJLUClientMainWindow::createUser);
    dialog.exec();
}

// 登录登出执行函数，调用一次函数发生一次状态反转

void CCJLUClientMainWindow::do_login_or_logout() {
    if (!CommandExecutor::owns_main_exe()) {
        QMessageBox::critical(this, "映像丢失！",
                              "请下载驱动程序！具体参考帮助文档指引！");
        showHelp();
        return;
    }
    if (is_logging) {
        logout();
    } else {
        login();
    }
}

// 登录逻辑
void CCJLUClientMainWindow::login() {
    LoginChecker checker;
    // 生成登录的命令行
    auto auth_check = checker.gain_command_list();
    if (!auth_check.first) {
        // 验证失败
        if (auth_check.second.size() != 0)
            QMessageBox::critical(this, "验证异常", auth_check.second.at(0));
        else
            // 在本设计中，目前尚不会出现无信息返回，因此这里占个坑 :)
            QMessageBox::critical(this, "验证异常",
                                  "未知异常！甚至不可能出现此对话框！");
        return;
    }

    // do_login
    __obj_tree_hold_label->setText("正在使用: " +
                                   collector.summon_file_path_name_only());
    ui->btn_login->setEnabled(false);
    command_executor->executeCommand(auth_check.second);
}

//  登出函数， 完成登出设置

void CCJLUClientMainWindow::logout() {
    command_executor->terminate_thread();
    movie_src->stop();
    statusBar()->showMessage("注销！");
    ui->btn_login->setText("登录");
    ui->action_login->setText("登录");
    is_logging = false;
}

void CCJLUClientMainWindow::showLoggerWindow() {
    window->show();
}

// 设置gif的动效是否开启

void CCJLUClientMainWindow::setMovieState(bool st) {
    if (st)
        movie_src->start();
    else
        movie_src->stop();
}

// 转发日志信息

void CCJLUClientMainWindow::handle_output_message(const QString msg) {
    // qDebug() << msg;
    window->append_output(msg);
}

// LoggerWindow分析日志返回登入成功逻辑

void CCJLUClientMainWindow::handle_connect_success() {
    if (!is_first_success) {
        movie_src->start();
        is_first_success = false;
        statusBar()->showMessage("连接成功", 30000);
    }
    is_logging = true;
    ui->btn_login->setText("取消登录");
    ui->action_login->setText("取消登录");
    ui->btn_login->setEnabled(true);
}

// LoggerWindow认为现在正在等待，等待的执行函数:

void CCJLUClientMainWindow::handle_waitings() {
    statusBar()->showMessage("正在连接中...");
}

// 连接可能超时，这里完成对用户的报错与提示

void CCJLUClientMainWindow::tell_possible_time_out() {
    QMessageBox::warning(this, "连接可能超时",
                         "连接可能存在超时！请检查您是否连接了JLU.PC");
    movie_src->stop();
    is_first_success = false;
}

// 连接超时，这里完成对用户的报错与提示

void CCJLUClientMainWindow::tell_time_out() {
    // 防止过多的call, 本来想SingleShot解决的，但是一想
    // 可能还会反复登入登出，还是使用一个最迷你的锁解决它 :)
    // 这里懒得换QMutex了
    static std::atomic_int _min_lock = 0;
    if (_min_lock == 0) {
        _min_lock = 1;
        QMessageBox::critical(this, "连接超时",
                              "连接超时！请检查您是否连接了JLU.PC");
    }
    _min_lock = 0;
    command_executor->terminate_thread();
    movie_src->stop();
    is_first_success = false;
    statusBar()->showMessage("连接超时");
    ui->btn_login->setEnabled(true);
}

// 验证失败逻辑

void CCJLUClientMainWindow::tell_auth_failed() {
    auto [user, passwd, mac] = collector.metaInfo();
    QMessageBox::critical(
        this, "验证失败",
        "验证失败，请重新检查您的用户名，和您的密码！用户名称: " + user);
    movie_src->stop();
    command_executor->terminate_thread();
    ui->btn_login->setEnabled(true);
    is_first_success = false;
}

// 最小化至托盘逻辑
void CCJLUClientMainWindow::minimize_to_hide() {
    tray_icon_instance.emit_show_st();
    this->hide();
}

// 直接执行退出

void CCJLUClientMainWindow::quit() {
    qApp->quit();
}

#include "Info/about/AboutInfo.h"

void CCJLUClientMainWindow::showAbout() {
    AboutInfo::showAbout(this);
}
void CCJLUClientMainWindow::showHelp() {
    if (!helpWindow) helpWindow = new HelpWindow(this);
    if (helpWindow->acquired_setText()) {
        helpWindow->setMarkDownString(HelpInfo::gainHelpMarkDown());
    }
    helpWindow->show();
}

void CCJLUClientMainWindow::closeEvent(QCloseEvent* closeEvent) {
    // query the status: shell miniximum to the tray?
    if (JLUClientTrayIcon::shell_switch_to_icon()) {
        minimize_to_hide();
        closeEvent->ignore();
    } else {
        closeEvent->accept();
        quit();
    }
}

CCJLUClientMainWindow::~CCJLUClientMainWindow() {
    delete ui;
}
