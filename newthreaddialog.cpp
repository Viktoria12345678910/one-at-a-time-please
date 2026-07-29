#include "newthreaddialog.h"
#include "ui_newthreaddialog.h"

NewThreadDialog::NewThreadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewThreadDialog)
{
    ui->setupUi(this);
}

NewThreadDialog::~NewThreadDialog()
{
    delete ui;
}

void NewThreadDialog::on_saveBtn_clicked()
{
    QString name = ui->nameLe->text();
    if(Database::instance().createThread(name) != -1){
        QMessageBox::information(this, tr("Успіх"), tr("гілку успішно створено"));
    } else {
        QMessageBox::critical(this, "error", "create thread returned false");
    }
    this->close();
}

