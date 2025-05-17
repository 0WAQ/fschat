#include "global.h"

std::function<void(QWidget*)> repolish = [](QWidget *w) -> void
{
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> encrypt = [](QString input) -> QString
{
    // TODO: 改用加密算法进行加密
    QString result = input;
    int len = result.length();
    int key = len % 255;

    // 对每一位进行异或
    for (int i = 0; i < len; ++i) {
        result[i] = QChar(static_cast<uchar>(input[i].unicode() ^ static_cast<uchar>(key)));
    }
    return result;
};

QString gate_url_prefix = "";
