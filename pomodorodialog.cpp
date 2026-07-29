#include "pomodorodialog.h"
#include "ui_pomodorodialog.h"

PomodoroDialog::PomodoroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PomodoroDialog),
    timer(new QTimer())
{
    qDebug()<<"------------Pomodoro Dialog----------------";
    qDebug()<<"constructor";
    QSettings settings;
    if(!settings.contains("workTime"))
        settings.setValue("workTime", "25");
    if(!settings.contains("restTime"))
        settings.setValue("restTime", "5");
    ui->setupUi(this);
    ui->pomodoroProgressBar->setMinimum(0);
    ui->pomodoroProgressBar->setValue(0);
    ui->pomodoroProgressBar->setTextVisible(true);

    connect(timer, &QTimer::timeout, this, &PomodoroDialog::updateProgress, Qt::QueuedConnection);
    showCharImg();
    int work = settings.value("workTime").toInt();
    int rest = settings.value("restTime").toInt();
    qDebug()<<"workTime: "<<work;
    qDebug()<<"restTime: "<<rest;
    ui->workTimeLb->setText(QString(tr("час роботи: %1")).arg(work));
    ui->ResTimelb->setText(QString(tr("час відпочинку: %1")).arg(rest));
}

PomodoroDialog::~PomodoroDialog()
{
    if(timer){
        timer->stop();
        timer->disconnect(this);
        timer->deleteLater();
        timer = nullptr;
    }

    delete ui;

}

void PomodoroDialog::showCharImg(){
    QSettings settings;
    QImage img = settings.value("charachterImg").value<QImage>();
    QPixmap charImg = QPixmap::fromImage(img);
    if(!charImg) return;
    ui->charachterLb->setPixmap(charImg.scaled(500, 500, Qt::KeepAspectRatio));

}

void PomodoroDialog::updateProgress(){
    if (!ui || !timer) return;
    if(remainingSec <= 0){
        timer->stop();
        return;
    }

    remainingSec--;
    ui->pomodoroProgressBar->setValue(remainingSec);
    int minutes = remainingSec / 60;
        int seconds = remainingSec % 60;

        ui->pomodoroProgressBar->setFormat(
            QString("%1:%2")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
        );
}

void PomodoroDialog::startWork()
{
    QSettings settings;
    int workTime = settings.value("workTime").toInt() * 60;
    timer->stop();
    ui->StateLb->setText(tr("працюємо"));
    remainingSec = workTime;
    ui->pomodoroProgressBar->setMaximum(workTime);
    ui->pomodoroProgressBar->setValue(workTime);


    timer->start(1000);
}

void PomodoroDialog::startRest()
{
    QSettings settings;
    int restTime = settings.value("restTime").toInt() * 60;
    timer->stop();
    ui->StateLb->setText(tr("відпочиваємо"));
    remainingSec = restTime;
    ui->pomodoroProgressBar->setValue(restTime);
    ui->pomodoroProgressBar->setMaximum(restTime);
    ui->pomodoroProgressBar->setValue(restTime);

    timer->start(1000);
}

void PomodoroDialog::stopTimer()
{
    timer->stop();
}

void PomodoroDialog::on_startWorkTimerBtn_clicked()
{
    startWork();
}


void PomodoroDialog::on_startRestTimerBtn_clicked()
{
    startRest();
}


void PomodoroDialog::on_stopTimerBtn_clicked()
{
    stopTimer();
}
