#ifndef TIMERBUTTON_H
#define TIMERBUTTON_H

#include <QPushButton>
#include <QTimer>

/**
 * @brief 计时器按钮
 */
class TimerButton : public QPushButton
{
public:
    TimerButton(QWidget *parent = nullptr);

    ~TimerButton();

    /**
     * @brief 鼠标释放后启动定时器
     */
    void mouseReleaseEvent(QMouseEvent* e) override;

private:
    QTimer* _timer;
    size_t _counter;
};

#endif // TIMERBUTTON_H
