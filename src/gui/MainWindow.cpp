#include "MainWindow.h"

#include <QAbstractItemView>
#include <QColor>
#include <QCheckBox>
#include <QComboBox>
#include <QFrame>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>
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
#include "dialogs/MysqlLoginDialog.h"
#include "dialogs/PGDetailsDialog.h"

namespace
{
QString toQString(const std::string &value)
{
    return QString::fromStdString(value);
}

QString formattedRent(int rent)
{
    return QString("Rs. %1").arg(
        QLocale(QLocale::English, QLocale::India).toString(rent)
    );
}

QFrame *createMetricCard(const QString &caption, QLabel *&valueLabel)
{
    auto *card = new QFrame;
    card->setObjectName("metricCard");

    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(18, 14, 18, 14);
    cardLayout->setSpacing(5);

    valueLabel = new QLabel("0", card);
    valueLabel->setObjectName("metricValue");
    cardLayout->addWidget(valueLabel);

    auto *captionLabel = new QLabel(caption, card);
    captionLabel->setObjectName("metricCaption");
    cardLayout->addWidget(captionLabel);
    return card;
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("StayNear - Student PG Accommodation");
    resize(1240, 760);
    setMinimumSize(900, 600);
    connectToMysql();
    createLayout();
    refreshPgs();
}

void MainWindow::connectToMysql()
{
    Database::Settings settings = Database::loadSettings();
    const auto useSampleData = [this](const QString &reason) {
        pgs_ = createSamplePgs();
        QMessageBox::warning(
            this,
            "MySQL unavailable",
            reason + "\n\nStayNear will use temporary sample data for this session."
        );
    };

    if (!database_.open(settings))
    {
        MysqlLoginDialog dialog(settings, this);
        if (dialog.exec() != QDialog::Accepted)
        {
            useSampleData(
                "Could not connect to MySQL:\n" +
                QString::fromStdString(database_.lastError())
            );
            return;
        }

        settings = dialog.settings();
        if (!database_.open(settings))
        {
            useSampleData(
                "Could not connect to MySQL:\n" +
                QString::fromStdString(database_.lastError())
            );
            return;
        }
    }

    if (!database_.seedIfEmpty(createSamplePgs()))
    {
        useSampleData(
            "StayNear could not initialize its database:\n" +
            QString::fromStdString(database_.lastError())
        );
        return;
    }

    pgs_ = database_.loadPgs();
    if (!database_.lastError().empty())
    {
        useSampleData(
            "StayNear could not load its listings:\n" +
            QString::fromStdString(database_.lastError())
        );
        return;
    }

    databaseReady_ = true;
    Database::saveSettings(settings);
}

void MainWindow::createLayout()
{
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(30, 22, 30, 24);
    layout->setSpacing(16);

    auto *header = new QHBoxLayout;
    header->setSpacing(12);

    auto *brandMark = new QLabel("SN");
    brandMark->setObjectName("brandMark");
    brandMark->setAlignment(Qt::AlignCenter);
    brandMark->setFixedSize(46, 46);
    header->addWidget(brandMark);

    auto *brandCopy = new QVBoxLayout;
    brandCopy->setSpacing(0);
    auto *brandName = new QLabel("StayNear");
    brandName->setObjectName("brandName");
    auto *brandTagline = new QLabel("STUDENT LIVING, MADE SIMPLE");
    brandTagline->setObjectName("brandTagline");
    brandCopy->addWidget(brandName);
    brandCopy->addWidget(brandTagline);
    header->addLayout(brandCopy);
    header->addStretch();

    connectionStatus_ = new QLabel;
    connectionStatus_->setObjectName("connectionStatus");
    connectionStatus_->setText(databaseReady_ ? "Connected to MySQL" : "Using sample data");
    connectionStatus_->setProperty("offline", !databaseReady_);
    header->addWidget(connectionStatus_);

    auto *registerButton = new QPushButton("Register a PG");
    registerButton->setObjectName("primaryButton");
    registerButton->setMinimumHeight(42);
    header->addWidget(registerButton);
    layout->addLayout(header);

    auto *pageTitle = new QLabel("Find a place that feels like home");
    pageTitle->setObjectName("pageTitle");
    layout->addWidget(pageTitle);

    auto *subtitle = new QLabel(
        "Explore student-friendly stays near GEHU and BIAS in Bhimtal."
    );
    subtitle->setObjectName("pageSubtitle");
    layout->addWidget(subtitle);

    auto *metrics = new QHBoxLayout;
    metrics->setSpacing(12);
    metrics->addWidget(createMetricCard("LISTED PROPERTIES", listingCount_));
    metrics->addWidget(createMetricCard("TOTAL BEDS", bedCount_));
    metrics->addWidget(createMetricCard("OCCUPIED BEDS", occupiedCount_));
    metrics->addWidget(createMetricCard("BEDS AVAILABLE", availableCount_));
    layout->addLayout(metrics);

    auto *filterPanel = new QFrame;
    filterPanel->setObjectName("filterPanel");
    auto *filterLayout = new QVBoxLayout(filterPanel);
    filterLayout->setContentsMargins(18, 14, 18, 16);
    filterLayout->setSpacing(10);

    auto *filterHeader = new QHBoxLayout;
    auto *filterTitle = new QLabel("Search and refine");
    filterTitle->setObjectName("sectionTitle");
    filterHeader->addWidget(filterTitle);
    filterHeader->addStretch();

    auto *clearButton = new QPushButton("Clear filters");
    clearButton->setObjectName("textButton");
    filterHeader->addWidget(clearButton);
    filterLayout->addLayout(filterHeader);

    auto *filters = new QHBoxLayout;
    filters->setSpacing(10);
    searchInput_ = new QLineEdit;
    searchInput_->setPlaceholderText("Search PG, college, or location");
    searchInput_->setClearButtonEnabled(true);
    searchInput_->setMinimumWidth(140);
    filters->addWidget(searchInput_, 1);

    typeFilter_ = new QComboBox;
    typeFilter_->addItems({"All types", "Boys", "Girls", "Co-Ed"});
    typeFilter_->setMinimumWidth(130);
    filters->addWidget(typeFilter_);

    availableFilter_ = new QCheckBox("Beds available");
    filters->addWidget(availableFilter_);
    filterLayout->addLayout(filters);

    auto *budgetPanel = new QFrame(filterPanel);
    budgetPanel->setObjectName("budgetInputFrame");
    auto *budgetLayout = new QHBoxLayout(budgetPanel);
    budgetLayout->setContentsMargins(12, 8, 12, 8);
    budgetLayout->setSpacing(12);

    auto *budgetCaption = new QLabel("Maximum monthly rent per bed");
    budgetCaption->setObjectName("budgetCaption");
    budgetLayout->addWidget(budgetCaption);
    budgetLayout->addStretch();

    budgetFilter_ = new QSpinBox(budgetPanel);
    budgetFilter_->setObjectName("budgetInput");
    budgetFilter_->setRange(0, 100000);
    budgetFilter_->setValue(10000);
    budgetFilter_->setPrefix("Rs. ");
    budgetFilter_->setGroupSeparatorShown(true);
    budgetFilter_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    budgetFilter_->setMinimumWidth(150);
    budgetFilter_->setAccessibleName("Maximum monthly rent per bed");
    budgetLayout->addWidget(budgetFilter_);
    filterLayout->addWidget(budgetPanel);
    layout->addWidget(filterPanel);

    auto *resultsHeader = new QHBoxLayout;
    auto *resultsTitle = new QLabel("Places to stay");
    resultsTitle->setObjectName("sectionTitle");
    resultsHeader->addWidget(resultsTitle);
    resultsHeader->addStretch();
    resultsLabel_ = new QLabel;
    resultsLabel_->setObjectName("resultCount");
    resultsHeader->addWidget(resultsLabel_);
    layout->addLayout(resultsHeader);

    pgTable_ = new QTableWidget(0, 8);
    pgTable_->setObjectName("pgTable");
    pgTable_->setHorizontalHeaderLabels({
        "PG name", "Nearby college", "Location", "Type",
        "Rent / bed", "Rating", "Rooms", "Beds available"
    });
    pgTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    pgTable_->setSelectionMode(QAbstractItemView::SingleSelection);
    pgTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pgTable_->setAlternatingRowColors(true);
    pgTable_->setShowGrid(false);
    pgTable_->setWordWrap(false);
    pgTable_->setAccessibleName("Available PG listings");
    pgTable_->verticalHeader()->hide();
    pgTable_->verticalHeader()->setDefaultSectionSize(50);
    pgTable_->horizontalHeader()->setMinimumHeight(42);
    pgTable_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    pgTable_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    pgTable_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    emptyState_ = new QLabel(
        "No stays match these filters.\nTry another search or clear your filters."
    );
    emptyState_->setObjectName("emptyState");
    emptyState_->setAlignment(Qt::AlignCenter);
    emptyState_->setWordWrap(true);
    emptyState_->setMinimumHeight(190);

    layout->addWidget(pgTable_, 1);
    layout->addWidget(emptyState_, 1);

    auto *footer = new QHBoxLayout;
    auto *helperText = new QLabel(
        databaseReady_
            ? "Listings are saved to your MySQL database."
            : "Sample listings are temporary and will reset when you close the app."
    );
    helperText->setObjectName("helperText");
    footer->addWidget(helperText);
    footer->addStretch();

    detailsButton_ = new QPushButton("View rooms");
    detailsButton_->setObjectName("secondaryButton");
    detailsButton_->setEnabled(false);
    detailsButton_->setMinimumHeight(40);
    footer->addWidget(detailsButton_);
    layout->addLayout(footer);

    setCentralWidget(centralWidget);

    connect(searchInput_, &QLineEdit::textChanged, this, [this] { refreshPgs(); });
    connect(typeFilter_, &QComboBox::currentTextChanged, this, [this] { refreshPgs(); });
    connect(budgetFilter_, &QSpinBox::valueChanged, this, [this](int) {
        refreshPgs();
    });
    connect(availableFilter_, &QCheckBox::toggled, this, [this] { refreshPgs(); });
    connect(clearButton, &QPushButton::clicked, this, [this] { clearFilters(); });
    connect(registerButton, &QPushButton::clicked, this, [this] { addPg(); });
    connect(detailsButton_, &QPushButton::clicked, this, [this] { showSelectedPg(); });
    connect(pgTable_, &QTableWidget::cellDoubleClicked, this,
        [this] { showSelectedPg(); });
    connect(pgTable_, &QTableWidget::itemSelectionChanged, this, [this] {
        detailsButton_->setEnabled(selectedPgIndex() >= 0);
    });
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

    pgTable_->setVisible(visibleCount > 0);
    emptyState_->setVisible(visibleCount == 0);
    detailsButton_->setEnabled(false);
    resultsLabel_->setText(
        QString("%1 of %2 listings").arg(visibleCount).arg(pgs_.size())
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
        formattedRent(pg.getRent()),
        QString("%1 / 5").arg(pg.getRating(), 0, 'f', 1),
        QString::number(pg.getTotalRooms()),
        QString("%1 available").arg(pg.getAvailableBedsCount())
    };

    for (int column = 0; column < values.size(); ++column)
    {
        auto *item = new QTableWidgetItem(values[column]);
        if (column == 0)
        {
            item->setData(Qt::UserRole, index);
            QFont nameFont = item->font();
            nameFont.setBold(true);
            item->setFont(nameFont);
        }
        if (column >= 4)
        {
            item->setTextAlignment(Qt::AlignCenter);
        }
        if (column == 7)
        {
            item->setForeground(
                pg.getAvailableBedsCount() > 0 ? QColor("#15803d") : QColor("#64748b")
            );
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

    listingCount_->setText(QString::number(pgs_.size()));
    bedCount_->setText(QString::number(totalBeds));
    occupiedCount_->setText(QString::number(occupiedBeds));
    availableCount_->setText(QString::number(availableBeds));
}

void MainWindow::clearFilters()
{
    searchInput_->clear();
    typeFilter_->setCurrentIndex(0);
    budgetFilter_->setValue(10000);
    availableFilter_->setChecked(false);
}

int MainWindow::selectedPgIndex() const
{
    // The first table cell stores which PG belongs to the selected row.
    const int row = pgTable_->currentRow();
    if (row < 0 || pgTable_->item(row, 0) == nullptr)
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

    const PG pg = dialog.createPG();
    if (databaseReady_ && !database_.savePg(pg))
    {
        QMessageBox::warning(
            this,
            "Could not save PG",
            "The PG was not added because MySQL could not save it:\n" +
                QString::fromStdString(database_.lastError())
        );
        return;
    }

    pgs_.push_back(pg);
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
