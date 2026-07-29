#ifndef CHANGEIMGDIALOG_H
#define CHANGEIMGDIALOG_H

#include <QDialog>
#include "database.h"
#include <QFileDialog>
#include <QBuffer>
#include "imports.h"

namespace Ui {
class ChangeImgDialog;
}

class ChangeImgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeImgDialog(QWidget *parent = nullptr);
    ~ChangeImgDialog();

private slots:
    void on_chooseBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::ChangeImgDialog *ui;
    void onSelectImg();
    QString filename;
};

#endif // CHANGEIMGDIALOG_H
