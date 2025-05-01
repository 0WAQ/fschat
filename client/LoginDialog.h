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

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
