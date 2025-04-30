#include "global.h"
#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // 密码框设置为 `密码模式`
    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->passwd_edit->setEchoMode(QLineEdit::Password);

    // 设置 error_tip_label 的属性
    ui->error_tip_label->setProperty("state", "normal");
    repolish(ui->error_tip_label);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTipMsg(QString msg, bool is_ok)
{
    ui->error_tip_label->setText(msg);
    ui->error_tip_label->setProperty("state", is_ok ? "normal" : "error");
    repolish(ui->error_tip_label);
}

void RegisterDialog::on_verify_button_clicked()
{
    auto email = ui->email_edit->text();

    // TAG: 该函数会被频繁调用, 故将 regex 对象设置为 static, 避免频繁构造
    static QRegularExpression regex{ R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)" };
    bool match = regex.match(email).hasMatch();
    if (match) {
        showTipMsg(tr("验证码已发送"), true);
        // TODO: 发送 http 验证码
    }
    else {
        showTipMsg(tr("无效的邮箱地址。"), false);
    }
}
