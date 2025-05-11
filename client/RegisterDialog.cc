#include "global.h"
#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

#include "HttpManager.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // 密码框设置为隐藏状态
    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    // 设置 error_tip_label 的属性
    ui->error_tip_label->setProperty("state", "normal");
    repolish(ui->error_tip_label);

    // 连接点击按钮和发出对应信号
    connect(ui->cancel_button, &QPushButton::clicked, this, &RegisterDialog::sig_switch_login);

    connect(&HttpManager::GetInstance(), &HttpManager::sig_mod_register_http_request_finish,
            this, &RegisterDialog::slot_mod_register_http_request_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::initHttpHandlers()
{
    // 注册 获取验证码
    _handlers.insert(RequestId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json) {
        int error = json["error"].toInt();
        if (error != ErrorCode::EC_SUCCESS) {
            showTipMsg(tr("验证码获取失败"), false);
            return;
        }

        // TODO: to be deleted
        auto email = json["email"].toString();
        showTipMsg(tr("验证码已发送, 请注意查收"), true);
        qDebug() << "email is " << email;

    });

    // 注册 用户注册
    _handlers.insert(RequestId::ID_REGISTER_USER, [this](const QJsonObject& json) {
        int error = json["error"].toInt();
        if (error != ErrorCode::EC_SUCCESS) {
            showTipMsg(tr("用户注册失败"), false);
            return;
        }

        // TODO: to be deleted
        auto email = json["email"].toString();
        showTipMsg(tr("用户注册成功"), true);
        qDebug() << "email is " << email;
    });
}

void RegisterDialog::showTipMsg(QString msg, bool is_ok)
{
    ui->error_tip_label->setText(msg);
    ui->error_tip_label->setProperty("state", is_ok ? "normal" : "error");
    repolish(ui->error_tip_label);
}

void RegisterDialog::on_verify_button_clicked()
{
    // 获取邮箱
    QString email = ui->email_edit->text();

    // TAG: 该函数会被频繁调用, 故将 regex 对象设置为 static, 避免频繁构造
    static QRegularExpression regex{ R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)" };
    bool match = regex.match(email).hasMatch();
    if (match) {
        // 发送 http 请求
        QJsonObject json;
        json["email"] = email;

        // TODO: 从配置文件中读取
        HttpManager::GetInstance().SendHttpRequest(QUrl(gate_url_prefix + "/get_verify_code"),
                                                   json, RequestId::ID_GET_VERIFY_CODE, Modules::MOD_REGISTER);
        showTipMsg(tr("验证码已发送"), true);
    }
    else {
        showTipMsg(tr("无效的邮箱地址"), false);
    }
}

void RegisterDialog::on_confirm_button_clicked()
{
    if (ui->user_edit->text().isEmpty()) {
        showTipMsg(tr("用户名不能为空"), false);
        return;
    }

    if (ui->email_edit->text().isEmpty()) {
        showTipMsg(tr("邮箱不能为空"), false);
        return;
    }

    // TODO: 为密码添加一些规则
    if (ui->passwd_edit->text().isEmpty()) {
        showTipMsg(tr("密码不能为空"), false);
        return;
    }

    if (ui->confirm_edit->text().isEmpty()) {
        showTipMsg(tr("确认密码不能为空"), false);
        return;
    }

    if (ui->passwd_edit->text() != ui->confirm_edit->text()) {
        showTipMsg(tr("密码和确认密码不匹配"), false);
        return;
    }

    if (ui->verify_edit->text().isEmpty()) {
        showTipMsg(tr("验证码不能为空"), false);
        return;
    }

    // 发送 http 请求: 注册用户
    QJsonObject json;
    json["user"] = ui->user_edit->text();
    json["email"] = ui->email_edit->text();
    json["passwd"] = ui->passwd_edit->text();
    json["confirm"] = ui->confirm_edit->text();
    json["verify_code"] = ui->verify_edit->text();
    HttpManager::GetInstance().SendHttpRequest(QUrl(gate_url_prefix + "/register"),
                                               json, RequestId::ID_REGISTER_USER, Modules::MOD_REGISTER);
}

void RegisterDialog::slot_mod_register_http_request_finish(RequestId id, QString res, ErrorCode ec)
{
    if (ec != ErrorCode::EC_SUCCESS) {
        showTipMsg(tr("网络请求错误"), false);
        return;
    }

    // 反序列化 json 字节流为 QJsonDocument (json 对象)
    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if (json.isNull()) {
        showTipMsg(tr("json解析失败"), false);
        return;
    }

    if(!json.isObject()) {
        showTipMsg(tr("无效的json对象"), false);
        return;
    }

    // 回调执行函数
    _handlers[id](json.object());
    return;
}
