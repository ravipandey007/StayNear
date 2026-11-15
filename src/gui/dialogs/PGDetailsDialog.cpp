#include "PGDetailsDialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include "Owner.h"
#include "PG.h"
#include "Room.h"
#include "Student.h"

namespace
{
QString toQString(const std::string &value)
{
    return QString::fromStdString(value);
}

// The same code works for an Owner or Student.
// getRole() calls the correct derived-class version (polymorphism).
QString describePerson(const Person &person)
{
    return QString("%1: %2, phone %3")
        .arg(toQString(person.getRole()))
        .arg(toQString(person.getName()))
        .arg(toQString(person.getPhone()));
}
}

PGDetailsDialog::PGDetailsDialog(const PG &pg, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(toQString(pg.getPGName()));
    resize(600, 560);

    QString details = QString(
        "PROPERTY DETAILS\n\n"
        "College: %1\n"
        "Location: %2\n"
        "Type: %3\n"
        "Monthly rent: Rs. %4 per bed\n"
        "Rating: %5 / 5\n"
        "\nOWNER CONTACT\n\n"
        "%6\n"
        "Email: %7\n\n"
        "ROOMS AND RESIDENTS\n"
    )
        .arg(toQString(pg.getCollegeName()))
        .arg(toQString(pg.getLocation()))
        .arg(toQString(pg.getPGType()))
        .arg(pg.getRent())
        .arg(pg.getRating(), 0, 'f', 1)
        .arg(describePerson(pg.getOwner()))
        .arg(toQString(pg.getOwner().getEmail()));

    for (const Room &room : pg.getRooms())
    {
        details += QString("\nRoom %1: %2 total, %3 occupied, %4 available\n")
            .arg(room.getRoomNumber())
            .arg(room.getTotalBeds())
            .arg(room.getOccupiedBeds())
            .arg(room.getAvailableBeds());

        for (const Student &student : room.getStudents())
        {
            details += QString("  %1, course %2, year %3\n")
                .arg(describePerson(student))
                .arg(toQString(student.getCourse()))
                .arg(student.getYear());
        }
    }

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 22, 24, 22);
    layout->setSpacing(12);

    auto *title = new QLabel(toQString(pg.getPGName()), this);
    title->setObjectName("dialogTitle");
    layout->addWidget(title);

    auto *subtitle = new QLabel(
        QString("%1  |  %2")
            .arg(toQString(pg.getCollegeName()))
            .arg(toQString(pg.getLocation())),
        this
    );
    subtitle->setObjectName("pageSubtitle");
    subtitle->setWordWrap(true);
    layout->addWidget(subtitle);

    auto *text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setPlainText(details);
    text->setMinimumHeight(300);
    layout->addWidget(text);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttons->button(QDialogButtonBox::Close)->setObjectName("secondaryButton");
    auto *buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    buttonRow->addWidget(buttons);
    layout->addLayout(buttonRow);
    connect(buttons, &QDialogButtonBox::rejected, this, &PGDetailsDialog::reject);
}
