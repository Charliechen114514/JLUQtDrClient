#include "HelpWindow.h"
#include "ui_HelpWindow.h"

HelpWindow::HelpWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::HelpWindow) {
    ui->setupUi(this);
    ui->textBrowser->setFont(QFont("Microsoft YaHei", 14));
}

void HelpWindow::setMarkDownString(const QString& buffers) {
    ui->textBrowser->setMarkdown(buffers);
}

bool HelpWindow::acquired_setText() const {
    return ui->textBrowser->toPlainText().isEmpty();
}

HelpWindow::~HelpWindow() {
    delete ui;
}
