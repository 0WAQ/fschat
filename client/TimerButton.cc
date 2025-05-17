#include "TimerButton.h"
#include <QMouseEvent>

TimerButton::TimerButton(QWidget *parent)
    : QPushButton(parent)
    , _timer(new QTimer(this))
    , _counter(60)
{
    // 为超时信号连接槽函数
    connect(_timer, &QTimer::timeout, [this]() {
        // 定时器超时后 --counter, 变为 0 后重置按钮
        if (--_counter <= 0) {
            _timer->stop();
            _counter = 60;
            this->setText(tr("获取"));
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(_counter) + tr("秒"));   // 显示剩余时间
    });
}

TimerButton::~TimerButton()
{
    _timer->stop();
}

void TimerButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 鼠标释放后启动定时器
    if (e->button() == Qt::LeftButton) {    // 鼠标左键释放事件
        qDebug() << "TimerButton was released!";

        this->setEnabled(false);
        this->setText(QString::number(_counter));
        _timer->start(1000);    // 每秒超时一次

        emit clicked();
    }

    // 调用基类操作
    QPushButton::mouseReleaseEvent(e);
}
