#include "MysqlLoginDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QSpinBox>
#include <QVBoxLayout>

MysqlLoginDialog::MysqlLoginDialog(const Database::Settings &settings, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Connect to MySQL");
    setMinimumWidth(420);

    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("StayNear needs MySQL", this);
    title->setObjectName("dialogTitle");
    layout->addWidget(title);
    auto *subtitle = new QLabel(
        "Enter the same login you use in MySQL Workbench. StayNear will create the staynear database.",
        this
    );
    subtitle->setObjectName("dialogSubtitle");
    subtitle->setWordWrap(true);
    layout->addWidget(subtitle);

    hostInput_ = new QLineEdit(QString::fromStdString(settings.host), this);
    portInput_ = new QSpinBox(this);
    portInput_->setRange(1, 65535);
    portInput_->setValue(settings.port);
    userInput_ = new QLineEdit(QString::fromStdString(settings.user), this);
    passwordInput_ = new QLineEdit(QString::fromStdString(settings.password), this);
    passwordInput_->setEchoMode(QLineEdit::Password);
    databaseInput_ = new QLineEdit(QString::fromStdString(settings.database), this);

    auto *form = new QFormLayout;
    form->setVerticalSpacing(10);
    form->addRow("Host:", hostInput_);
    form->addRow("Port:", portInput_);
    form->addRow("User:", userInput_);
    form->addRow("Password:", passwordInput_);
    form->addRow("Database:", databaseInput_);
    layout->addLayout(form);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttons->button(QDialogButtonBox::Ok)->setObjectName("primaryButton");
    buttons->button(QDialogButtonBox::Ok)->setText("Connect");
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &MysqlLoginDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &MysqlLoginDialog::reject);
}

Database::Settings MysqlLoginDialog::settings() const
{
    Database::Settings values;
    values.host = hostInput_->text().trimmed().toStdString();
    values.port = portInput_->value();
    values.user = userInput_->text().trimmed().toStdString();
    values.password = passwordInput_->text().toStdString();
    values.database = databaseInput_->text().trimmed().toStdString();
    return values;
}

void MysqlLoginDialog::accept()
{
    if (hostInput_->text().trimmed().isEmpty() ||
        userInput_->text().trimmed().isEmpty() ||
        databaseInput_->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Missing information", "Please enter host, user, and database name.");
        return;
    }

    static const QRegularExpression databaseNamePattern("^[A-Za-z0-9_]{1,64}$");
    if (!databaseNamePattern.match(databaseInput_->text().trimmed()).hasMatch())
    {
        QMessageBox::warning(
            this,
            "Invalid database name",
            "Use 1 to 64 letters, numbers, or underscores for the database name."
        );
        return;
    }

    QDialog::accept();
}
