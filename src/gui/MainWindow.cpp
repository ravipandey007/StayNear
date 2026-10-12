#include "MainWindow.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QComboBox>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

#include "SampleData.h"
#include "dialogs/AddPGDialog.h"
#include "dialogs/PGDetailsDialog.h"

namespace
{
QString toQString(const std::string &value)
{
    return QString::fromStdString(value);
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pgs_(createSamplePgs())
{
    setWindowTitle("StayNear - Student PG Accommodation");
    resize(1100, 700);
    createLayout();
    refreshPgs();
}

void MainWindow::createLayout()
{
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    auto *title = new QLabel("StayNear - Student PG Accommodation");
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 5);
    titleFont.setBold(true);
    title->setFont(titleFont);
    layout->addWidget(title);
    layout->addWidget(new QLabel(
        "Browse PGs near GEHU and BIAS in Bhimtal, or register a new PG."
    ));

    summaryLabel_ = new QLabel;
    layout->addWidget(summaryLabel_);

    auto *filters = new QHBoxLayout;
    searchInput_ = new QLineEdit;
    searchInput_->setPlaceholderText("Search PG, college, or location");
    filters->addWidget(searchInput_, 1);

    typeFilter_ = new QComboBox;
    typeFilter_->addItems({"All types", "Boys", "Girls", "Co-Ed"});
    filters->addWidget(typeFilter_);

    budgetFilter_ = new QSpinBox;
    budgetFilter_->setRange(0, 100000);
    budgetFilter_->setValue(10000);
    budgetFilter_->setPrefix("Max rent: Rs. ");
    filters->addWidget(budgetFilter_);

    availableFilter_ = new QCheckBox("Available beds only");
    filters->addWidget(availableFilter_);
    layout->addLayout(filters);

    pgTable_ = new QTableWidget(0, 8);
    pgTable_->setHorizontalHeaderLabels({
        "PG name", "College", "Location", "Type",
        "Rent / month", "Rating", "Rooms", "Beds available"
    });
    pgTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    pgTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    pgTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pgTable_->setAlternatingRowColors(true);
    pgTable_->verticalHeader()->hide();
    pgTable_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    pgTable_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    layout->addWidget(pgTable_, 1);

    auto *buttons = new QHBoxLayout;
    resultsLabel_ = new QLabel;
    buttons->addWidget(resultsLabel_);
    buttons->addStretch();

    auto *addButton = new QPushButton("Register PG");
    auto *detailsButton = new QPushButton("View rooms");
    buttons->addWidget(addButton);
    buttons->addWidget(detailsButton);
    layout->addLayout(buttons);

    setCentralWidget(centralWidget);

    connect(searchInput_, &QLineEdit::textChanged, this, [this] { refreshPgs(); });
    connect(typeFilter_, &QComboBox::currentTextChanged, this, [this] { refreshPgs(); });
    connect(budgetFilter_, &QSpinBox::valueChanged, this, [this] { refreshPgs(); });
    connect(availableFilter_, &QCheckBox::toggled, this, [this] { refreshPgs(); });
    connect(addButton, &QPushButton::clicked, this, [this] { addPg(); });
    connect(detailsButton, &QPushButton::clicked, this, [this] { showSelectedPg(); });
    connect(pgTable_, &QTableWidget::cellDoubleClicked, this,
        [this] { showSelectedPg(); });
}

void MainWindow::refreshPgs()
{
    // Rebuild the table using the current search and filter choices.
    pgTable_->setRowCount(0);
    int visibleCount = 0;
    const QString query = searchInput_->text().trimmed();
    const QString type = typeFilter_->currentText();

    for (std::size_t index = 0; index < pgs_.size(); ++index)
    {
        const PG &pg = pgs_[index];
        const int availableBeds = pg.getAvailableBedsCount();
        const bool matchesQuery =
            toQString(pg.getPGName()).contains(query, Qt::CaseInsensitive) ||
            toQString(pg.getCollegeName()).contains(query, Qt::CaseInsensitive) ||
            toQString(pg.getLocation()).contains(query, Qt::CaseInsensitive);
        const bool matchesType = type == "All types" || toQString(pg.getPGType()) == type;
        const bool matchesRent = pg.getRent() <= budgetFilter_->value();
        const bool hasAvailableBeds = !availableFilter_->isChecked() || availableBeds > 0;

        if (!matchesQuery || !matchesType || !matchesRent || !hasAvailableBeds)
        {
            continue;
        }

        addPgRow(pg, static_cast<int>(index));
        ++visibleCount;
    }

    resultsLabel_->setText(
        QString("Showing %1 of %2 PGs").arg(visibleCount).arg(pgs_.size())
    );
    updateSummary();
}

void MainWindow::addPgRow(const PG &pg, int index)
{
    const int row = pgTable_->rowCount();
    pgTable_->insertRow(row);

    const QStringList values = {
        toQString(pg.getPGName()),
        toQString(pg.getCollegeName()),
        toQString(pg.getLocation()),
        toQString(pg.getPGType()),
        QString::number(pg.getRent()),
        QString::number(pg.getRating(), 'f', 1),
        QString::number(pg.getTotalRooms()),
        QString::number(pg.getAvailableBedsCount())
    };

    for (int column = 0; column < values.size(); ++column)
    {
        auto *item = new QTableWidgetItem(values[column]);
        if (column == 0)
        {
            item->setData(Qt::UserRole, index);
        }
        pgTable_->setItem(row, column, item);
    }
}

void MainWindow::updateSummary()
{
    int totalBeds = 0;
    int occupiedBeds = 0;
    int availableBeds = 0;

    for (const PG &pg : pgs_)
    {
        totalBeds += pg.getTotalBedsCount();
        occupiedBeds += pg.getOccupiedBedsCount();
        availableBeds += pg.getAvailableBedsCount();
    }

    summaryLabel_->setText(
        QString("PGs: %1    Total beds: %2    Occupied: %3    Available: %4")
            .arg(pgs_.size())
            .arg(totalBeds)
            .arg(occupiedBeds)
            .arg(availableBeds)
    );
}

int MainWindow::selectedPgIndex() const
{
    // The first table cell stores which PG belongs to the selected row.
    const int row = pgTable_->currentRow();
    if (row < 0)
    {
        return -1;
    }

    return pgTable_->item(row, 0)->data(Qt::UserRole).toInt();
}

void MainWindow::addPg()
{
    // The dialog gathers the form values and creates a PG object.
    AddPGDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    pgs_.push_back(dialog.createPG());
    refreshPgs();
}

void MainWindow::showSelectedPg()
{
    const int index = selectedPgIndex();
    if (index < 0)
    {
        QMessageBox::information(this, "Select a PG", "Select a PG from the list first.");
        return;
    }

    PGDetailsDialog dialog(pgs_[static_cast<std::size_t>(index)], this);
    dialog.exec();
}
