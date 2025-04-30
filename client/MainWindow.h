/**
 * @author  bwb
 * @date    2025/04/30
 * @brief   主窗口
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "LoginDialog.h"
#include "RegisterDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:

    void SlotSwitchRegister();

private:
    Ui::MainWindow *ui;

    LoginDialog *_login_dialog;
    RegisterDialog *_register_dialog;
};
#endif // MAINWINDOW_H
