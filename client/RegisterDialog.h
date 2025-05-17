#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMap>

#include "global.h"

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
     * @brief 初始化 handlers, 注册 http 请求发送成功后执行的回调函数
     */
    void initHttpHandlers();

    /**
     * @brief 修改邮箱行状态, 并显示提示信息
     */
    void showTipMsg(QString msg, bool is_ok);

    /**
     * @brief 注册完成后跳转到完成注册页面
     */
    void changeTipPage();

    void addTipErr(TipErr te, QString tips);
    void delTipErr(TipErr te);

    /**
     * @brief 用于动态地检查输入是否合理
     */
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPasswdValid();
    bool checkConfirmValid();
    bool checkVerifyValid();

signals:
    void sig_switch_login();

private slots:
    void on_verify_button_clicked();    // 注册界面点击获取按钮
    void on_confirm_button_clicked();   // 注册界面点击确认按钮

    void on_passwd_action_triggered();
    void on_confirm_action_triggered();

    void on_return_button_clicked();

public slots:
    /**
     * @brief 槽函数, 收到 http 请求
     */
    void slot_mod_register_http_request_finish(RequestId id, QString res, ErrorCode ec);

private:
    Ui::RegisterDialog *ui;

    QMap<RequestId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;

    /**
     * @brief 注册成功后, 返回登录界面的计时器
     */
    QTimer* _timer;
    int _count;
};

#endif // REGISTERDIALOG_H
