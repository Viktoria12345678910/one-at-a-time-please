#ifndef POMODORODIALOG_H
#define POMODORODIALOG_H

#include <QDialog>
#include <QTimer>
#include "database.h"
#include <QCloseEvent>
#include "imports.h"

namespace Ui {
class PomodoroDialog;
}

class PomodoroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PomodoroDialog(QWidget *parent = nullptr);
    ~PomodoroDialog();

private slots:
    void updateProgress();

    void on_startWorkTimerBtn_clicked();

    void on_startRestTimerBtn_clicked();

    void on_stopTimerBtn_clicked();


private:
    Ui::PomodoroDialog *ui = nullptr;
    void showCharImg();
    void startWork();
    void startRest();
    void stopTimer();

    QTimer *timer = nullptr;
    int remainingSec = 1;

};

#endif // POMODORODIALOG_H
