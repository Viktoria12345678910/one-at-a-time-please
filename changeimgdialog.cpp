#include "changeimgdialog.h"
#include "ui_changeimgdialog.h"

ChangeImgDialog::ChangeImgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeImgDialog)
{
    ui->setupUi(this);
}

ChangeImgDialog::~ChangeImgDialog()
{
    delete ui;
}

void ChangeImgDialog::on_chooseBtn_clicked()
{
    filename = QFileDialog::getOpenFileName(
        this, tr("Вибрати обкладинку"), "", tr("Зображення (*.png *.jpg *.jpeg)"));

    if (!filename.isEmpty()) {
        QPixmap pixmap(filename);
        if (!pixmap.isNull()) {
            ui->PreviewLb->setPixmap(pixmap.scaled(500, 500, Qt::KeepAspectRatio));
        }
    }
}


void ChangeImgDialog::on_saveBtn_clicked()
{
    qDebug()<<"----------------ChangeImgDialog-----------------";
    qDebug()<<"on_saveBtn_clicked()";
    if (!filename.isEmpty()) {
        QImage charachterImg(filename);
        QSettings settings;
        qDebug()<<"settings: "<<settings.applicationName();
        settings.setValue("charachterImg", charachterImg);
    }
    this->close();
}

