#ifndef ADDPGDIALOG_H
#define ADDPGDIALOG_H

#include <QDialog>

#include "PG.h"

class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QSpinBox;

// Qt form for entering a new PG and its owner/room information.
class AddPGDialog : public QDialog
{
public:
    explicit AddPGDialog(QWidget *parent = nullptr);
    PG createPG() const;

private:
    void accept() override;

    QLineEdit *nameInput_;
    QLineEdit *collegeInput_;
    QLineEdit *locationInput_;
    QComboBox *typeInput_;
    QSpinBox *rentInput_;
    QDoubleSpinBox *ratingInput_;
    QLineEdit *ownerNameInput_;
    QLineEdit *ownerPhoneInput_;
    QLineEdit *ownerEmailInput_;
    QSpinBox *roomCountInput_;
    QSpinBox *bedsPerRoomInput_;
};

#endif
