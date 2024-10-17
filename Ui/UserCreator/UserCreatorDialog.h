#ifndef USERCREATORDIALOG_H
#define USERCREATORDIALOG_H
#include <QDialog>

class CCJLUClientMainWindow;

namespace Ui {
class UserCreatorDialog;
}

class UserCreatorDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserCreatorDialog(CCJLUClientMainWindow *window,
                               QWidget               *parent = nullptr);
    ~UserCreatorDialog();
signals:

    void tellUserInfo(const QString user, const QString passwd);
private slots:
    void handle_creation();
    void handle_close();

private:
    Ui::UserCreatorDialog *ui;
};

#endif  // USERCREATORDIALOG_H
