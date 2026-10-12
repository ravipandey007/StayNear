#include "AddPGDialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QSpinBox>

#include "Owner.h"
#include "Room.h"

AddPGDialog::AddPGDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Register a PG");
    auto *form = new QFormLayout(this);

    nameInput_ = new QLineEdit(this);
    collegeInput_ = new QLineEdit("Graphic Era Hill University Bhimtal", this);
    locationInput_ = new QLineEdit(this);

    typeInput_ = new QComboBox(this);
    typeInput_->addItems({"Boys", "Girls", "Co-Ed"});

    rentInput_ = new QSpinBox(this);
    rentInput_->setRange(1000, 30000);
    rentInput_->setValue(5500);

    ratingInput_ = new QDoubleSpinBox(this);
    ratingInput_->setRange(0.0, 5.0);
    ratingInput_->setSingleStep(0.1);
    ratingInput_->setValue(4.5);

    ownerNameInput_ = new QLineEdit(this);
    ownerPhoneInput_ = new QLineEdit(this);
    ownerEmailInput_ = new QLineEdit(this);

    roomCountInput_ = new QSpinBox(this);
    roomCountInput_->setRange(1, 20);
    roomCountInput_->setValue(2);

    bedsPerRoomInput_ = new QSpinBox(this);
    bedsPerRoomInput_->setRange(1, 6);
    bedsPerRoomInput_->setValue(2);

    form->addRow("PG name:", nameInput_);
    form->addRow("Nearby college:", collegeInput_);
    form->addRow("Location:", locationInput_);
    form->addRow("PG type:", typeInput_);
    form->addRow("Monthly rent per bed:", rentInput_);
    form->addRow("Rating:", ratingInput_);
    form->addRow("Owner name:", ownerNameInput_);
    form->addRow("Owner phone:", ownerPhoneInput_);
    form->addRow("Owner email:", ownerEmailInput_);
    form->addRow("Number of rooms:", roomCountInput_);
    form->addRow("Beds per room:", bedsPerRoomInput_);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel,
        this
    );
    form->addRow(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &AddPGDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &AddPGDialog::reject);
}

void AddPGDialog::accept()
{
    // Require the important text fields before closing the form.
    if (nameInput_->text().trimmed().isEmpty() ||
        collegeInput_->text().trimmed().isEmpty() ||
        locationInput_->text().trimmed().isEmpty() ||
        ownerNameInput_->text().trimmed().isEmpty() ||
        ownerPhoneInput_->text().trimmed().isEmpty() ||
        ownerEmailInput_->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Missing information", "Please complete all fields.");
        return;
    }

    QDialog::accept();
}

PG AddPGDialog::createPG() const
{
    // Turn the form values into normal C++ model objects.
    PG pg(
        nameInput_->text().trimmed().toStdString(),
        collegeInput_->text().trimmed().toStdString(),
        locationInput_->text().trimmed().toStdString(),
        typeInput_->currentText().toStdString(),
        rentInput_->value(),
        static_cast<float>(ratingInput_->value())
    );
    pg.setOwner(Owner(
        ownerNameInput_->text().trimmed().toStdString(),
        ownerPhoneInput_->text().trimmed().toStdString(),
        ownerEmailInput_->text().trimmed().toStdString()
    ));

    for (int room = 0; room < roomCountInput_->value(); ++room)
    {
        pg.addRoom(Room(101 + room, bedsPerRoomInput_->value()));
    }

    return pg;
}
