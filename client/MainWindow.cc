#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _login_dialog(new LoginDialog(this)),
    _register_dialog(new RegisterDialog(this))
{
    ui->setupUi(this);

    setCentralWidget(_login_dialog);

    // 收到 switchRegister 信号时, 调用 SlotSwitchRegister 槽函数
    connect(_login_dialog, &LoginDialog::SwitchRegister, this, &MainWindow::slot_switch_register);

    // 将 dialog 嵌入到 CentralWidget 中
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _register_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _register_dialog->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_switch_register()
{
    // 隐藏 login 界面, 显示 register 界面
    setCentralWidget(_register_dialog);
    _login_dialog->hide();
    _register_dialog->show();
}
