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

signals:
    /**
     * @brief 信号, 用于切换到注册界面, 会执行 MainWindow::slot_switch_register 槽函数
     */
    void sig_switch_register();

private slots:
    void on_login_button_clicked();     // 登录界面点击登录按钮

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
