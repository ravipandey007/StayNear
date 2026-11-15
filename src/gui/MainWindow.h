#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "Database.h"
#include "PG.h"

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QTableWidget;

// Main screen: search PGs, filter the list, and open the two dialogs.
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void connectToMysql();
    void createLayout();
    void refreshPgs();
    void addPgRow(const PG &pg, int index);
    void updateSummary();
    void clearFilters();
    void addPg();
    void showSelectedPg();
    int selectedPgIndex() const;

    Database database_;
    bool databaseReady_ = false;
    std::vector<PG> pgs_;
    QLineEdit *searchInput_ = nullptr;
    QComboBox *typeFilter_ = nullptr;
    QSpinBox *budgetFilter_ = nullptr;
    QCheckBox *availableFilter_ = nullptr;
    QTableWidget *pgTable_ = nullptr;
    QLabel *listingCount_ = nullptr;
    QLabel *bedCount_ = nullptr;
    QLabel *occupiedCount_ = nullptr;
    QLabel *availableCount_ = nullptr;
    QLabel *connectionStatus_ = nullptr;
    QLabel *emptyState_ = nullptr;
    QLabel *resultsLabel_ = nullptr;
    QPushButton *detailsButton_ = nullptr;
};

#endif
