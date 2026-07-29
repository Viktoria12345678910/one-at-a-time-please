#include "changethemedialog.h"
#include "ui_changethemedialog.h"

ChangeThemeDialog::ChangeThemeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeThemeDialog)
{

    ui->setupUi(this);
    loadThemes();
}

ChangeThemeDialog::~ChangeThemeDialog()
{
    delete ui;
}

void ChangeThemeDialog::on_saveBtn_clicked()
{
    qDebug()<<"---------ChangeThemeDialog---------------";
    qDebug()<<"on_saveBtn_clicked";
    QString theme = ui->themeCb->currentText();

    QSettings settings;
    settings.setValue("theme", theme);

    this->close();

}

void ChangeThemeDialog::loadThemes()
{
    qDebug()<<"---------ChangeThemeDialog---------------";
    qDebug()<<"loadThemes()";
    Theme themeClass;
    QSettings settings;
    QStringList themes = themeClass.getAvailableThemes();
    ui->themeCb->clear();
    qDebug()<<"cleared combo box";

    for (QString theme : themes) {
        theme.remove(".qss");
        qDebug()<<"handling: "<<theme;

        ui->themeCb->addItem(theme);
    }
    qDebug()<<"done populating combo box";

    QString cTheme = settings.value("theme").toString();
    ui->themeCb->setCurrentText(cTheme);
}

