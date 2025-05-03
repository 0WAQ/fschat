#include "global.h"
#include "MainWindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/StyleSheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("Open Success.");
        QString style = qss.readAll();
        // TODO: 颜色自适应
        a.setStyleSheet(style);
        qss.close();
    }
    else {
        qDebug("Open Failed!");
    }

    // 读取 config.ini 配置文件
    QString config_path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()
                                                   + QDir::separator() + "config.ini");
    QSettings settings{ config_path, QSettings::IniFormat };

    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
