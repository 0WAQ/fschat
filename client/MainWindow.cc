#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建 login 界面为 MainWindow 的中心部件
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _login_dialog->show();
    setCentralWidget(_login_dialog);

    // login 界面收到 switch_register 信号时, 调用 slot_switch_register 槽函数
    connect(_login_dialog, &LoginDialog::sig_switch_register, this, &MainWindow::slot_switch_register);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_switch_register()
{
    // 创建 register 界面为 MainWindow 的中心界面
    _register_dialog = new RegisterDialog(this);
    _register_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // register 界面收到 switch_login 信号时, 调用 slot_switch_login 槽函数
    connect(_register_dialog, &RegisterDialog::sig_switch_login, this, &MainWindow::slot_switch_login);

    _login_dialog->hide();
    _register_dialog->show();
    setCentralWidget(_register_dialog);
}

void MainWindow::slot_switch_login()
{
    // 创建 login 界面为 MainWindow 的中心界面
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // login 界面收到 switch_register 信号时, 调用 slot_switch_register 槽函数
    connect(_login_dialog, &LoginDialog::sig_switch_register, this, &MainWindow::slot_switch_register);

    _register_dialog->hide();
    _login_dialog->show();
    setCentralWidget(_login_dialog);
}
