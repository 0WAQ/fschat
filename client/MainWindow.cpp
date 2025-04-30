#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _login_dialog(new LoginDialog())
    , _register_dialog(new RegisterDialog())
{
    ui->setupUi(this);

    setCentralWidget(_login_dialog);
    _login_dialog->show();

    // 收到 switchRegister 信号时, 调用 SlotSwitchRegister 槽函数
    connect(_login_dialog, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchRegister);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (_login_dialog) {
        delete _login_dialog;
        _login_dialog = nullptr;
    }

    if (_register_dialog) {
        delete _register_dialog;
        _register_dialog = nullptr;
    }
}

void MainWindow::SlotSwitchRegister()
{
    // 隐藏 login 界面, 显示 register 界面
    setCentralWidget(_register_dialog);
    _login_dialog->hide();
    _register_dialog->show();
}
