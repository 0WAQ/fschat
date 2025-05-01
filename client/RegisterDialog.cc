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
    // connect(ui->confirm_button, &QPushButton::clicked, this, nullptr);  // TODO:
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
    // 注册 验证码获取
    _handlers.insert(RequestId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json) {
        int error = json["error"].toInt();
        if (error != ErrorCode::EC_SUCCESS) {
            showTipMsg(tr("参数错误"), false);
            return;
        }

        auto email = json["email"].toString();
        showTipMsg(tr("验证码已发送, 请注意查收"), true);
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
        showTipMsg(tr("验证码已发送"), true);
        // TODO: 发送 http 验证码
    }
    else {
        showTipMsg(tr("无效的邮箱地址"), false);
    }
}

void RegisterDialog::on_confirm_button_clicked()
{

}

void RegisterDialog::on_cancel_button_clicked()
{

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
