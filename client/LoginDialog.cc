#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 密码框设置为隐藏状态
    ui->passwd_edit->setEchoMode(QLineEdit::Password);

    // 点击 register_button 时, 发起 switch_register 信号
    connect(ui->register_button, &QPushButton::clicked, this, &LoginDialog::sig_switch_register);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
