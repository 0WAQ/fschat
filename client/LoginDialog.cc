#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 点击 register_button 时, 发起 switchRegister 信号
    connect(ui->register_button, &QPushButton::clicked, this, &LoginDialog::switchRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
