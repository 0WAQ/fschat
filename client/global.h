#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QStyle>
#include <QRegularExpression>

#include <functional>

/**
 * @brief 用于刷新 qss 文件
 */
extern std::function<void(QWidget*)> repolish;

#endif // GLOBAL_H
