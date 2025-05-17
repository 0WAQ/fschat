#include "global.h"
#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

#include "HttpManager.h"

#include <QToolButton>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
    , _timer(new QTimer(this))
    , _count(5)
{
    ui->setupUi(this);

    // 设置密码框和确认框的显示模式
    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    // 添加可以切换可见性的 Action
    ui->passwd_edit->addAction(ui->passwd_action, QLineEdit::TrailingPosition);
    ui->confirm_edit->addAction(ui->confirm_action, QLineEdit::TrailingPosition);

    // 设置 Action 的图标
    ui->passwd_action->setIcon(QIcon(":/res/unvisible.png"));
    ui->confirm_action->setIcon(QIcon(":/res/unvisible.png"));

    // 设置 error_tip_label 的属性
    ui->error_tip_label->setProperty("state", "normal");
    ui->error_tip_label->clear();
    repolish(ui->error_tip_label);

    // 连接点击按钮和发出对应信号
    connect(ui->cancel_button, &QPushButton::clicked, this, &RegisterDialog::sig_switch_login);

    // 动态的错误提示
    connect(ui->user_edit, &QLineEdit::editingFinished, this, &RegisterDialog::checkUserValid);
    connect(ui->email_edit, &QLineEdit::editingFinished, this, &RegisterDialog::checkEmailValid);
    connect(ui->passwd_edit, &QLineEdit::editingFinished, this, &RegisterDialog::checkPasswdValid);
    connect(ui->confirm_edit, &QLineEdit::editingFinished, this, &RegisterDialog::checkConfirmValid);
    connect(ui->verify_edit, &QLineEdit::editingFinished, this, &RegisterDialog::checkVerifyValid);

    // 注册成功, 5秒后返回登录界面 或者 直接返回
    connect(_timer, &QTimer::timeout, this, [this]() {
        if (--_count <= 0) {
            _timer->stop();
            emit sig_switch_login();
            return;
        }
        auto msg = QString(tr("注册成功，%1秒后返回登录界面").arg(_count));
        ui->tip_label->setText(msg);
    });

    connect(&HttpManager::GetInstance(), &HttpManager::sig_mod_register_http_request_finish,
            this, &RegisterDialog::slot_mod_register_http_request_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::initHttpHandlers()
{
    // 注册 获取验证码
    _handlers.insert(RequestId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json) {
        int error = json["error"].toInt();
        if (error != ErrorCode::EC_SUCCESS) {
            showTipMsg(tr("验证码获取失败"), false);
            return;
        }
        showTipMsg(tr("验证码已发送, 请注意查收"), true);

        qDebug() << "email is " << json["email"].toString();;

    });

    // 注册 用户注册
    _handlers.insert(RequestId::ID_REGISTER_USER, [this](const QJsonObject& json) {
        switch (json["error"].toInt())
        {
        case ErrorCode::EC_REGISTER_SUCCESS:
            showTipMsg(tr("用户注册成功"), true);
            qDebug() << "uid is " << json["uid"].toString();
            changeTipPage();    // 切换至 完成注册 界面
            break;
        case ErrorCode::EC_REGISTER_MYSQL_EXCEPTION:
            showTipMsg(tr("用户注册失败, MySQL异常"), false);
            break;
        case ErrorCode::EC_REGISTER_EXPIRED_VERIFY_CODE:
            showTipMsg(tr("用户注册失败, 验证码已过期, 请重新获取"), false);
            break;
        case ErrorCode::EC_REGISTER_VERIFY_CODE_ERROR:
            showTipMsg(tr("用户注册失败, 验证码错误, 请重新输入"), false);
            break;
        case ErrorCode::EC_REGISTER_USER_EXIST:
            showTipMsg(tr("用户注册失败, 用户名已存在"), false);
            break;
        case ErrorCode::EC_REGISTER_EMAIL_EXIST:
            showTipMsg(tr("用户注册失败, 邮箱已存在"), false);
            break;
        default:
            break;
        }
    });
}

void RegisterDialog::showTipMsg(QString msg, bool is_ok)
{
    ui->error_tip_label->setText(msg);
    ui->error_tip_label->setProperty("state", is_ok ? "normal" : "error");
    repolish(ui->error_tip_label);
}

void RegisterDialog::changeTipPage()
{
    // _timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    // 启动定时器
    _timer->start(1000);
}

void RegisterDialog::addTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTipMsg(tips, false);
}

void RegisterDialog::delTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if (_tip_errs.isEmpty()) {
        ui->error_tip_label->clear();
        return;
    }
    showTipMsg(_tip_errs.first(), false);
}

bool RegisterDialog::checkUserValid()
{
    if (ui->user_edit->text().isEmpty()) {
        addTipErr(TipErr::TIP_USER_ERR ,tr("用户名不能为空"));
        return false;
    }

    delTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->email_edit->text();

    // 邮箱地址的正则表达式
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");

    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match) {
        addTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }

    delTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkPasswdValid()
{
    auto pwd = ui->passwd_edit->text();

    if (pwd.isEmpty()) {
        addTipErr(TipErr::TIP_PWD_ERR, tr("密码不能为空"));
        return false;
    }

    if (pwd.length() < 6 || pwd.length()> 15) {
        addTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应在 6 ~ 15 位"));
        return false;
    }

    // 密码长度至少6, 可以是字母, 数字和指定的特殊字符 (!@#$%^&*)
    static QRegularExpression regex("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regex.match(pwd).hasMatch();
    if (!match) {
        addTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;
    }

    delTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    auto confirm = ui->confirm_edit->text();
    if (confirm.isEmpty()) {
        addTipErr(TipErr::TIP_CONFIRM_ERR, tr("确认密码不能为空"));
        return false;
    }

    auto pwd = ui->passwd_edit->text();

    // 先按长度比较
    if (pwd.length() != confirm.length()){
        addTipErr(TipErr::TIP_PWD_CONFIRM_ERR, tr("密码与确认密码长度不一致"));
        return false;
    }
    else if (pwd != confirm) {
        addTipErr(TipErr::TIP_PWD_CONFIRM_ERR, tr("密码与确认密码不一致"));
        return false;
    }

    delTipErr(TipErr::TIP_PWD_CONFIRM_ERR);
    return true;
}

bool RegisterDialog::checkVerifyValid()
{
    auto verify_code = ui->verify_edit->text();
    if (verify_code.isEmpty()) {
        addTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    if (verify_code.length() != 4) {
        addTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码长度为4位"));
        return false;
    }

    delTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}

void RegisterDialog::on_verify_button_clicked()
{
    // 获取邮箱
    QString email = ui->email_edit->text();

    // TAG: 该函数会被频繁调用, 故将 regex 对象设置为 static, 避免频繁构造
    static QRegularExpression regex{ R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)" };
    bool match = regex.match(email).hasMatch();
    if (match) {
        // 发送 http 请求
        QJsonObject json;
        json["email"] = email;

        showTipMsg(tr("验证码发送中"), true);
        // TODO: 从配置文件中读取
        HttpManager::GetInstance().SendHttpRequest(QUrl(gate_url_prefix + "/get_verify_code"),
                                                   json, RequestId::ID_GET_VERIFY_CODE, Modules::MOD_REGISTER);
    }
    else {
        showTipMsg(tr("无效的邮箱地址"), false);
    }
}

void RegisterDialog::on_confirm_button_clicked()
{
    if (!checkUserValid()
        || !checkEmailValid()
        || !checkPasswdValid()
        || !checkConfirmValid()
        || !checkVerifyValid())
    {
        return;
    }

    // 发送 http 请求: 注册用户
    QJsonObject json;
    json["user"] = ui->user_edit->text();
    json["email"] = ui->email_edit->text();
    json["passwd"] = encrypt(ui->passwd_edit->text());
    json["confirm"] = encrypt(ui->confirm_edit->text());
    json["verify_code"] = ui->verify_edit->text();
    HttpManager::GetInstance().SendHttpRequest(QUrl(gate_url_prefix + "/register"),
                                               json, RequestId::ID_REGISTER_USER, Modules::MOD_REGISTER);
}

void RegisterDialog::slot_mod_register_http_request_finish(RequestId id, QString res, ErrorCode ec)
{
    if (ec != ErrorCode::EC_SUCCESS) {
        showTipMsg(tr("网络请求错误"), false);
        return;
    }

    // 反序列化 json 字节流为 QJsonDocument (json 对象)
    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if (json.isNull()) {
        showTipMsg(tr("json解析失败"), false);
        return;
    }

    if(!json.isObject()) {
        showTipMsg(tr("无效的json对象"), false);
        return;
    }

    // 回调执行函数
    _handlers[id](json.object());
    return;
}

void RegisterDialog::on_passwd_action_triggered()
{
    if (ui->passwd_edit->echoMode() == QLineEdit::Normal) {
        ui->passwd_edit->setEchoMode(QLineEdit::Password);
        ui->passwd_action->setIcon(QIcon(":/res/unvisible.png"));
    }
    else {
        ui->passwd_edit->setEchoMode(QLineEdit::Normal);
        ui->passwd_action->setIcon(QIcon(":/res/visible.png"));
    }
}

void RegisterDialog::on_confirm_action_triggered()
{
    if (ui->confirm_edit->echoMode() == QLineEdit::Normal) {
        ui->confirm_edit->setEchoMode(QLineEdit::Password);
        ui->confirm_action->setIcon(QIcon(":/res/unvisible.png"));
    }
    else {
        ui->confirm_edit->setEchoMode(QLineEdit::Normal);
        ui->confirm_action->setIcon(QIcon(":/res/visible.png"));
    }
}

void RegisterDialog::on_return_button_clicked()
{
    _timer->stop();
    emit sig_switch_login();
}

