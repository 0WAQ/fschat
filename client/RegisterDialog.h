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
     * @brief 初始化 handlers
     */
    void initHttpHandlers();

    /**
     * @brief 修改邮箱行状态, 并显示提示信息
     */
    void showTipMsg(QString msg, bool is_ok);

signals:
    void sig_switch_login();

private slots:
    void on_verify_button_clicked();    // 注册界面点击获取按钮
    void on_confirm_button_clicked();   // 注册界面点击确认按钮

public slots:
    /**
     * @brief 槽函数, 收到 http 请求
     */
    void slot_mod_register_http_request_finish(RequestId id, QString res, ErrorCode ec);

private:
    Ui::RegisterDialog *ui;

    QMap<RequestId, std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTERDIALOG_H
