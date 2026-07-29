#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QMessageBox>
#include "pomodorodialog.h"
#include "pomodorosettingsdialog.h"
#include "newtaskdialog.h"
#include "newthreaddialog.h"
#include "changeimgdialog.h"
#include "changelanguagedialog.h"
#include <QSettings>
#include "changethemedialog.h"
#include "viewttdialog.h"
#include "models/thread.h"
#include "models/task.h"
#include "imports.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QTranslator translator;
    void applyLanguage();

private slots:
    void on_markAsDoneBtn_clicked();

    void on_threadBox_currentIndexChanged(int index);

    void on_taskNameCb_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void loadThreads();
    void loadTasks();
    void startPomodoro();
    void charImg();
    void pomodoroSettings();
    void newTask();
    void newThread();
    void changeImg();
    void changeLang();
    void changeTheme();
    bool applyTheme();
    void viewTT();
    void loadLang();

};
#endif // MAINWINDOW_H
