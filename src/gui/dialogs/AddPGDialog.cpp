#include "AddPGDialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

#include "Owner.h"
#include "Room.h"

AddPGDialog::AddPGDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Register a PG");
    setMinimumWidth(540);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 22, 24, 22);
    layout->setSpacing(12);

    auto *title = new QLabel("Register your PG", this);
    title->setObjectName("dialogTitle");
    layout->addWidget(title);

    auto *subtitle = new QLabel(
        "Add property, owner, and room information for your listing.",
        this
    );
    subtitle->setObjectName("pageSubtitle");
    layout->addWidget(subtitle);

    auto *propertyGroup = new QGroupBox("Property details", this);
    auto *propertyForm = new QFormLayout(propertyGroup);
    propertyForm->setHorizontalSpacing(14);
    propertyForm->setVerticalSpacing(9);
    propertyForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    nameInput_ = new QLineEdit(propertyGroup);
    collegeInput_ = new QLineEdit("Graphic Era Hill University Bhimtal", propertyGroup);
    locationInput_ = new QLineEdit(propertyGroup);

    typeInput_ = new QComboBox(propertyGroup);
    typeInput_->addItems({"Boys", "Girls", "Co-Ed"});

    rentInput_ = new QSpinBox(propertyGroup);
    rentInput_->setRange(1000, 30000);
    rentInput_->setValue(5500);
    rentInput_->setPrefix("Rs. ");

    ratingInput_ = new QDoubleSpinBox(propertyGroup);
    ratingInput_->setRange(0.0, 5.0);
    ratingInput_->setSingleStep(0.1);
    ratingInput_->setValue(4.5);
    ratingInput_->setSuffix(" / 5");

    propertyForm->addRow("PG name:", nameInput_);
    propertyForm->addRow("Nearby college:", collegeInput_);
    propertyForm->addRow("Location:", locationInput_);
    propertyForm->addRow("PG type:", typeInput_);
    propertyForm->addRow("Monthly rent per bed:", rentInput_);
    propertyForm->addRow("Rating:", ratingInput_);
    layout->addWidget(propertyGroup);

    auto *ownerGroup = new QGroupBox("Owner contact", this);
    auto *ownerForm = new QFormLayout(ownerGroup);
    ownerForm->setHorizontalSpacing(14);
    ownerForm->setVerticalSpacing(9);
    ownerForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    ownerNameInput_ = new QLineEdit(ownerGroup);
    ownerPhoneInput_ = new QLineEdit(ownerGroup);
    ownerEmailInput_ = new QLineEdit(ownerGroup);
    ownerEmailInput_->setPlaceholderText("name@example.com");

    ownerForm->addRow("Owner name:", ownerNameInput_);
    ownerForm->addRow("Owner phone:", ownerPhoneInput_);
    ownerForm->addRow("Owner email:", ownerEmailInput_);
    layout->addWidget(ownerGroup);

    auto *roomsGroup = new QGroupBox("Room capacity", this);
    auto *roomsForm = new QFormLayout(roomsGroup);
    roomsForm->setHorizontalSpacing(14);
    roomsForm->setVerticalSpacing(9);
    roomsForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    roomCountInput_ = new QSpinBox(roomsGroup);
    roomCountInput_->setRange(1, 20);
    roomCountInput_->setValue(2);

    bedsPerRoomInput_ = new QSpinBox(roomsGroup);
    bedsPerRoomInput_->setRange(1, 6);
    bedsPerRoomInput_->setValue(2);

    roomsForm->addRow("Number of rooms:", roomCountInput_);
    roomsForm->addRow("Beds per room:", bedsPerRoomInput_);
    layout->addWidget(roomsGroup);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel,
        this
    );
    buttons->button(QDialogButtonBox::Save)->setObjectName("primaryButton");
    buttons->button(QDialogButtonBox::Save)->setText("Save PG");
    auto *buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    buttonRow->addWidget(buttons);
    layout->addLayout(buttonRow);

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
