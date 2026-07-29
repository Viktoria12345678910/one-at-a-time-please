#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <QDateTime>
#include <QString>
#include <QTranslator>
#include <QLocale>
#include <QMessageBox>
#include "models/task.h"
#include "models/thread.h"
#include "imports.h"

class Database
{
public:
    static Database& instance();
    bool connect(const QString &path = "library.db");
    void disconnect();

    bool createTables();

    // Tasks methods
    int createTask(const QString &name, const QString &description,
                      int threadId);
    bool completeTask(int taskId);
    Task getTask(int taskId);
    QList<Task> getTasksByThread(int threadId);

    // Settings methods
    bool changeCharachterImg(const QString &path);
    bool changeTheme(int themeId);
    bool changePomodoro(int work, int rest);
    QPixmap getCharachterImg();
    int getWorkTime();
    int getRestTime();

    // thread methods
    int createThread(const QString &name);
    bool isAllComplete(int threadId); //archiving
    bool Archive(int threadId);
    Thread getThread(int threadId);
    QList<Thread> getAllThreads();

    bool deleteTask(int taskId);
    bool deleteThread(int threadId);
    bool deleteTheme(int themeId);
    bool wipe();

    QString error(){return mDb.lastError().text();}

    QSqlDatabase getDatabase() { return mDb; }

private:
    Database();
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase mDb;
};

#endif // DATABASE_H