#ifndef POMODOROSETTINGSDIALOG_H
#define POMODOROSETTINGSDIALOG_H

#include <QDialog>
#include "database.h"
#include "imports.h"

namespace Ui {
class PomodoroSettingsDialog;
}

class PomodoroSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PomodoroSettingsDialog(QWidget *parent = nullptr);
    ~PomodoroSettingsDialog();

private slots:
    void on_saveSettingsBtn_clicked();

private:
    Ui::PomodoroSettingsDialog *ui;
};

#endif // POMODOROSETTINGSDIALOG_H
