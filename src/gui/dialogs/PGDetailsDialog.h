#ifndef PGDETAILSDIALOG_H
#define PGDETAILSDIALOG_H

#include <QDialog>

class PG;
class QWidget;

// Read-only window showing one PG, its rooms, and its residents.
class PGDetailsDialog : public QDialog
{
public:
    explicit PGDetailsDialog(const PG &pg, QWidget *parent = nullptr);
};

#endif
