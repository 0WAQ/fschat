#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

signals:
    /**
     * @brief 信号, 用于切换到注册界面, 会执行 MainWindow::SlotSwitchRegister 槽函数
     */
    void switchRegister();
};

#endif // LOGINDIALOG_H
