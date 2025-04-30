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

    MainWindow w;
    w.show();
    return a.exec();
}
