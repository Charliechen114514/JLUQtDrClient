#include "UserCreatorDialog.h"
#include <QMessageBox>
#include "CCJLUClientMainWindow.h"
#include "ui_UserCreatorDialog.h"
UserCreatorDialog::UserCreatorDialog(CCJLUClientMainWindow *window,
                                     QWidget               *parent)
    : QDialog(parent), ui(new Ui::UserCreatorDialog) {
    ui->setupUi(this);
    connect(ui->btn_ensure, &QPushButton::clicked, this,
            &UserCreatorDialog::handle_creation);
    connect(window, &CCJLUClientMainWindow::tell_close_dialog, this,
            &UserCreatorDialog::handle_close);
}

void UserCreatorDialog::handle_creation() {
    auto res = std::pair<QString, QString>(ui->lineEdit_username->text(),
                                           ui->lineEdit_passwd->text());
    if (res.first.isEmpty() || res.second.isEmpty()) {
        QMessageBox::critical(this, "发生错误", "用户密码不可以为空！");
        return;
    }
    emit tellUserInfo(res.first, res.second);
}

void UserCreatorDialog::handle_close() {
    QMessageBox::information(this, "创建用户配置文件成功",
                             "创建用户配置文件成功");
    this->close();
}

UserCreatorDialog::~UserCreatorDialog() {
    delete ui;
}
