#ifndef MYSQLLOGINDIALOG_H
#define MYSQLLOGINDIALOG_H

#include <QDialog>

#include "Database.h"

class QLineEdit;
class QSpinBox;

// Collects MySQL connection details the first time the app runs.
class MysqlLoginDialog : public QDialog
{
public:
    explicit MysqlLoginDialog(const Database::Settings &settings, QWidget *parent = nullptr);
    Database::Settings settings() const;

private:
    void accept() override;

    QLineEdit *hostInput_;
    QSpinBox *portInput_;
    QLineEdit *userInput_;
    QLineEdit *passwordInput_;
    QLineEdit *databaseInput_;
};

#endif
