#ifndef NEWTHREADDIALOG_H
#define NEWTHREADDIALOG_H

#include <QDialog>
#include "database.h"
#include "imports.h"

namespace Ui {
class NewThreadDialog;
}

class NewThreadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewThreadDialog(QWidget *parent = nullptr);
    ~NewThreadDialog();

private slots:
    void on_saveBtn_clicked();

private:
    Ui::NewThreadDialog *ui;
};

#endif // NEWTHREADDIALOG_H
