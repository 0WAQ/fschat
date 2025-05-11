#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 密码框设置为隐藏状态
    ui->passwd_edit->setEchoMode(QLineEdit::Password);

    connect(ui->login_button, &QPushButton::clicked, this, &LoginDialog::on_login_button_clicked);
    connect(ui->register_button, &QPushButton::clicked, this, &LoginDialog::sig_switch_register);
}

void LoginDialog::on_login_button_clicked()
{
    // TODO:
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
