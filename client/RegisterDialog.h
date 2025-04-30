#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    /**
     * @brief 修改邮箱行状态, 并显示提示信息
     * @param msg 提示信息
     * @param is_ok 判断邮箱格式是否正确
     */
    void showTipMsg(QString msg, bool is_ok);

private slots:
    /**
     * @brief 槽函数, 点击获取验证码时, 用于验证邮箱是否否和格式
     */
    void on_verify_button_clicked();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
