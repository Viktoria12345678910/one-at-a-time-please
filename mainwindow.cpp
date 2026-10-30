#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(Database::instance().connect()){
        ui->statusbar->showMessage("підключення до бази даних успішне");
    } else {
        QString msg = Database::instance().error();
        ui->statusbar->showMessage(QString("no connect \n %1").arg(msg));
    }


    connect(ui->startPomodoroA, &QAction::triggered, this, &MainWindow::startPomodoro);
    connect(ui->editPomodoroA, &QAction::triggered, this, &MainWindow::pomodoroSettings);
    connect(ui->NewTaskA, &QAction::triggered, this, &MainWindow::newTask);
    connect(ui->NewThreadA, &QAction::triggered, this, &MainWindow::newThread);
    connect(ui->changeCharachterA, &QAction::triggered, this, &MainWindow::changeImg);
    connect(ui->changeLangA, &QAction::triggered, this, &MainWindow::changeLang);
    //connect(ui->changeThemeA, &QAction::triggered, this, &MainWindow::changeTheme);
    connect(ui->ViewTTA, &QAction::triggered, this, &MainWindow::viewTT);

    charImg();
    loadThreads();
    loadTasks();
    applyLanguage();
    //applyTheme();
}

MainWindow::~MainWindow()
{
    Database::instance().disconnect();
    delete ui;
}

void MainWindow::startPomodoro()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"startPomodoro()";
    PomodoroDialog pomodoro;
    pomodoro.setModal(true);
    pomodoro.exec();
}

void MainWindow::pomodoroSettings()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"pomodoroSettings";
    PomodoroSettingsDialog pomodoroSettings;
    pomodoroSettings.exec();
}

void MainWindow::newTask()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"newTask()";
    NewTaskDialog newTask;
    newTask.exec();
}

void MainWindow::newThread()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"newThread()";
    NewThreadDialog newThread;
    newThread.exec();
    loadThreads();
}

void MainWindow::changeImg()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"changeImg()";
    ChangeImgDialog changeImg;
    changeImg.exec();
    charImg();
}

void MainWindow::charImg()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"charImg()";
    QSettings settings;
    QImage img = settings.value("charachterImg").value<QImage>();
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->charachterImgLabel->setAlignment(Qt::AlignCenter);
    ui->charachterImgLabel->setPixmap(pixmap.scaled(500, 500, Qt::KeepAspectRatio));
}

void MainWindow::changeLang()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"changeLang()";
    ChangeLanguageDialog *changeLang = new ChangeLanguageDialog(this);
    if(changeLang->exec() == QDialog::Accepted){
        applyLanguage();
    }
}

// void MainWindow::changeTheme()
// {
//     qDebug()<<"----------MainWindow----------";
//     qDebug()<<"changeTheme()";
//     ChangeThemeDialog *changeTheme = new ChangeThemeDialog(this);
//     applyTheme();
//     changeTheme->exec();
//     applyTheme();
// }

void MainWindow::viewTT()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"viewTT()";
    ViewTTDialog *view = new ViewTTDialog(this);
    view->exec();
    loadThreads();
    loadTasks();
}

void MainWindow::on_markAsDoneBtn_clicked()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"on_markAsDoneBtn_clicked()";
    ui->statusbar->showMessage(tr("Чудово, так тримати"));
    int taskId = ui->taskNameCb->currentData().toInt();
    qDebug()<<"MainWindow: taskId is "<<taskId;
    Task task = Database::instance().getTask(taskId);
    qDebug() << "completing task: "<<task.name;
    Database::instance().completeTask(taskId);
    loadTasks();

}

void MainWindow::loadThreads()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"loadThreads()";
    qDebug() << "load threads called";
    ui->threadBox->blockSignals(true);
    ui->threadBox->clear();
    ui->threadBox->addItem(" ",-1);
    qDebug()<< "combo box cleared";
    QList<Thread> threads = Database::instance().getAllThreads();
    qDebug() << "threads recieved";
    for (auto &thread : threads){
    qDebug()<<"handlig: "<<thread.name;
    QString arch;
    if(thread.archived){
        arch = tr("гілку заархівовано");
    } else {
            arch = tr("гілку не заархівовано");
    }
        ui->threadBox->addItem(
            QString("%1 (%2)").arg(thread.name, arch), thread.threadId); //
    }
    ui->threadBox->blockSignals(false);
}

void MainWindow::loadTasks()
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"loadTasks()";
    qDebug() << "load tasks called";
    ui->taskNameCb->blockSignals(true);
    ui->taskNameCb->clear();
    ui->taskNameCb->addItem(" ",-1);
    int currentThread = ui->threadBox->currentData().toInt();
    qDebug()<< "combo box cleared";
    QList<Task> tasks = Database::instance().getTasksByThread(currentThread);
    qDebug() << "tasks recieved";

    for (auto &task : tasks){
    qDebug()<<"handlig: "<<task.name;
    QString arch;
    if(task.completed == 1){
        arch = tr("завдання виконано ✅");
    } else {
            arch = tr("завдання не виконано");
    }
        ui->taskNameCb->addItem(QString("%1 (%2)").arg(task.name, arch), task.taskId);
    }
    ui->taskNameCb->blockSignals(false);
}


void MainWindow::applyLanguage()
{
    qDebug() << "----------MainWindow----------";
    qDebug() << "applyLanguage()";

    auto *dialog = new QProgressDialog(tr("Processing, please wait..."), QString(), 0, 0, this);
        dialog->setWindowModality(Qt::WindowModal);
        dialog->setCancelButton(nullptr); // Remove cancel button if task can't be stopped
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();

        // 2. Set up a watcher to auto-close the dialog when the work completes
        auto *watcher = new QFutureWatcher<void>(this);

        connect(watcher, &QFutureWatcher<void>::finished, dialog, &QProgressDialog::accept);
        connect(watcher, &QFutureWatcher<void>::finished, watcher, &QObject::deleteLater);
        connect(watcher, &QFutureWatcher<void>::finished, this, [this, watcher]() {
                ui->retranslateUi(this);
                watcher->deleteLater();
            });

    QFuture<void> future = QtConcurrent::run([this]() {
            loadLang();
            QThread::sleep(5); // Example work
        });

    watcher->setFuture(future);

}

void MainWindow::loadLang()
{
    QSettings settings;
    QString language = settings.value("language").toString();

    qApp->removeTranslator(&translator);

    if (!language.isEmpty()) {
        // Match the :/i18n directory where your files actually live
        QString path = QString(":/i18n/one_at_a_time_please_%1.qm").arg(language);


        if (translator.load(path)) {

            qApp->installTranslator(&translator);
            qDebug() << "Successfully loaded language from:" << path;
        } else {
            qDebug() << "Failed to load language from:" << path;
        }
    }
}


// bool MainWindow::applyTheme()
// {
//     qDebug()<<"----------MainWindow----------";
//     qDebug()<<"applyTheme()";

//     auto *dialog = new QProgressDialog(tr("Processing, please wait..."), QString(), 0, 0, this);
//         dialog->setWindowModality(Qt::WindowModal);
//         dialog->setCancelButton(nullptr); // Remove cancel button if task can't be stopped
//         dialog->setAttribute(Qt::WA_DeleteOnClose);
//         dialog->show();

//     QSettings settings;
//     Theme theme;
//     QString themeFileName = settings.value("theme").toString() + ".qss";
//     QString filePath = QDir(theme.getThemesPath()).filePath(themeFileName);
//         QFile file(filePath);

//         if (!file.open(QFile::ReadOnly | QFile::Text)) {
//             qDebug() << "Failed to open theme file:" << filePath;
//             return false;
//         }

//         QTextStream stream(&file);
//         QString stylesheet = stream.readAll();
//         file.close();

//         // Apply globally to the whole application
//         qApp->setStyleSheet(stylesheet);

//         qDebug() << "Applied theme:" << themeFileName;
//         return true;
// }


void MainWindow::on_threadBox_currentIndexChanged(int index)
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"on_threadBox_currentIndexChanged(int index)";
    if(index>=0){
        loadTasks();
    } else {
        qDebug()<<"no thread selected.returning";
        return;
    }
}


void MainWindow::on_taskNameCb_currentIndexChanged(int index)
{
    qDebug()<<"----------MainWindow----------";
    qDebug()<<"on_taskNameCb_currentIndexChanged(int index)";
    if(index>=0){
        Task currentTask = Database::instance().getTask(index);
        ui->curentTaskDescLb->setText(currentTask.description);
    } else {
        qDebug()<<"no task selected. Returning";
        return;
    }
}

