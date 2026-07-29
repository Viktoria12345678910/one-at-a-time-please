#include "changelanguagedialog.h"
#include "ui_changelanguagedialog.h"

ChangeLanguageDialog::ChangeLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLanguageDialog)
{
    ui->setupUi(this);
    loadLanguages();
}

ChangeLanguageDialog::~ChangeLanguageDialog()
{
    delete ui;
}

void ChangeLanguageDialog::loadLanguages()
{
    QSettings settings;
    // 1. Check if the /i18n resource path exists
        QDir dir(":/i18n");

        qDebug() << "Resource dir exists:" << dir.exists();
        qDebug() << "Files found in :/i18n:" << dir.entryList(QDir::Files);

        // 2. Declare rootDir before using it to debug all embedded resources
        QDir rootDir(":/");
        qDebug() << "Root resource contents:" << rootDir.entryList();

        // 3. Populate your ComboBox
        QStringList files = dir.entryList(QDir::Files);

        ui->langCb->clear();

        for (QString file : files) {
            file.remove("one_at_a_time_please_");
            file.remove(".qm");

            ui->langCb->addItem(file);
        }
        QString cLang = settings.value("language").toString();
        ui->langCb->setCurrentText(cLang);


}

void ChangeLanguageDialog::on_saveBtn_clicked()
{
    QString lang = ui->langCb->currentText();

    QSettings settings;
    settings.setValue("language", lang);

    this->accept();

}
