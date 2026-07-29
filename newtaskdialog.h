#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>
#include "database.h"
#include "imports.h"

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = nullptr);
    ~NewTaskDialog();

private slots:
    void on_saveBtn_clicked();

private:
    Ui::NewTaskDialog *ui;
    void loadThreads();
};

#endif // NEWTASKDIALOG_H
