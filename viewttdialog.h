#ifndef VIEWTTDIALOG_H
#define VIEWTTDIALOG_H

#include <QDialog>
#include "database.h"
#include <QStandardItemModel>
#include "imports.h"

namespace Ui {
class ViewTTDialog;
}

class ViewTTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewTTDialog(QWidget *parent = nullptr);
    ~ViewTTDialog();

private slots:
    void on_deleteBtn_clicked();

    void on_collapseBtn_clicked();

    void on_expandBtn_clicked();

    void on_wipedbtn_clicked();

private:
    Ui::ViewTTDialog *ui;
    QStandardItemModel *model;
    void DBWipe();
    enum ItemType
    {
        ThreadItem,
        TaskItem
    };
    enum Role
    {
        TypeRole = Qt::UserRole + 1,
        IdRole
    };
};

#endif // VIEWTTDIALOG_H
