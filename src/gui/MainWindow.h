#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "PG.h"

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QTableWidget;

// Main screen: search PGs, filter the list, and open the two dialogs.
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createLayout();
    void refreshPgs();
    void addPgRow(const PG &pg, int index);
    void updateSummary();
    void addPg();
    void showSelectedPg();
    int selectedPgIndex() const;

    std::vector<PG> pgs_;
    QLineEdit *searchInput_ = nullptr;
    QComboBox *typeFilter_ = nullptr;
    QSpinBox *budgetFilter_ = nullptr;
    QCheckBox *availableFilter_ = nullptr;
    QTableWidget *pgTable_ = nullptr;
    QLabel *summaryLabel_ = nullptr;
    QLabel *resultsLabel_ = nullptr;
};

#endif
