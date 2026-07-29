#include "pomodorosettingsdialog.h"
#include "ui_pomodorosettingsdialog.h"

PomodoroSettingsDialog::PomodoroSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PomodoroSettingsDialog)
{
    QSettings settings;
    ui->setupUi(this);
    int currentWork = settings.value("workTime").toInt();
    int currentRest = settings.value("restTime").toInt();
    ui->WorkTimeSb->setValue(currentWork);
    ui->restTimeSb->setValue(currentRest);
}

PomodoroSettingsDialog::~PomodoroSettingsDialog()
{
    delete ui;
}

void PomodoroSettingsDialog::on_saveSettingsBtn_clicked()
{
    int work = ui->WorkTimeSb->value();
    int rest = ui->restTimeSb->value();
    QSettings settings;
    settings.setValue("workTime", work);
    settings.setValue("restTime", rest);
    this->close();
}

