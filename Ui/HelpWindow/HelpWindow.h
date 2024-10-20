#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    bool acquired_setText() const;
    void setMarkDownString(const QString &buffers);
    ~HelpWindow();

private:
    Ui::HelpWindow *ui;
};

#endif  // HELPWINDOW_H
