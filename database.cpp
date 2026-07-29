#include "database.h"
#include <QtSql>
#include <QtWidgets>
#include <QMessageBox>


Database& Database::instance()
{
    //db
    static Database instance;
    return instance;
}

Database::Database()
{
    //db
}

Database::~Database()
{
    //db
    disconnect();
}

bool Database::connect(const QString &path)
{
    //db
    qDebug()<<"---------Database------------";
    qDebug()<<"connect(const QString &path)";
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(path);

    if (!mDb.open())
        {
            QMessageBox::critical(
                nullptr,
                "Database Error",
                mDb.lastError().text()
            );
            qDebug()<<"error: "<<mDb.lastError().text();
    qDebug() << "Database: connection ok";
    return true;
    }
    return createTables();
}

void Database::disconnect()
{
    //db
    qDebug()<<"---------Database------------";
    qDebug()<<"disconnect()";
    if (mDb.isOpen()) {
        mDb.close();
    }
}

bool Database::createTables()
{
    //
    qDebug()<<"---------Database------------";
    qDebug()<<"createTables()";
    QSqlQuery query;



    // Create threads table
    QString createThreads = R"(
        CREATE TABLE IF NOT EXISTS threads (
            threadId INTEGER PRIMARY KEY AUTOINCREMENT,
            threadName TEXT NOT NULL,
            isArchived BOOLEAN DEFAULT 0
        )
    )";

    if (!query.exec(createThreads)) {
        qDebug() << "Error creating threads table:" << query.lastError();
        return false;
    } else {
        qDebug() <<"threads created succesfully";
    }

    // Create tasks table
    QString createTasks = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            taskId INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            threadId INTEGER NOT NULL,
            complete BOOLEAN DEFAULT 0,
            current  BOOLEAN DEFAULT 0,
            FOREIGN KEY (threadId) REFERENCES threads(threadId)
        )
    )";

    if (!query.exec(createTasks)) {
        qDebug() << "Error creating tasks table:" << query.lastError();
        return false;
    } else {
        qDebug() << "table tasks create succesfully";
    }

    qDebug() << "All tables created successfully";
    return true;
}

//tasks
int Database::createTask(const QString &name, const QString &description, int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"createTask(const QString &name, const QString &description, int threadId)";
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO tasks (name, description, threadId, complete)
        VALUES (:taskName, :taskDesc, :threadId, false)
    )");
    query.bindValue(":taskName", name);
    query.bindValue(":taskDesc",description);
    query.bindValue(":threadId", threadId);

    if (!query.exec()) {
        qDebug() << "Error creating task:" << query.lastError();
        return -1;
    }

    return query.lastInsertId().toInt();
}

//tasks
bool Database::completeTask(int taskId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"completeTask(taskId)";
    qDebug()<<"completing task with id of "<<taskId;
    QSqlQuery query;
    query.prepare(R"(
        UPDATE tasks SET complete = true WHERE taskId = ?
)");
    query.addBindValue(taskId);
    if(query.exec()){
        qDebug()<<"task completed succesfully";
    } else {
        qDebug()<<"task not completed due to database issues: "<<query.lastError().text();
        qDebug()<<query.lastQuery();

    }
    return query.exec();
}


//threads
int Database::createThread(const QString &name)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"createThread(const QString &name)";
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO threads (threadName, isArchived)
        VALUES(:threadName, 0)
    )");
    query.bindValue(":threadName", name);
    if (!query.exec()) {
        qDebug() << "Error creating thread:" << query.lastError();
        return -1;
    }
    return query.lastInsertId().toInt();
}

//tasks
bool Database::deleteTask(int taskId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"deleteTask(int taskId)";
    QSqlQuery query;
    query.prepare(R"(
        DELETE FROM tasks WHERE taskId = :taskId
    )");
    query.bindValue(":taskId", taskId);
    if (!query.exec()) {
        qDebug() << "Error deleting task:" << query.lastError();
        return -1;
    }
    return query.exec();
}

// threads
bool Database::deleteThread(int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"deleteThread(int threadId)";
    QSqlQuery query;
    query.prepare(R"(
        DELETE FROM threads WHERE threadId = :threadId
    )");
    query.bindValue(":threadId", threadId);
    if (!query.exec()) {
        qDebug() << "Error deleting thread:" << query.lastError();
        return -1;
    }
    return query.exec();
}

// tasks
Task Database::getTask(int taskId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"getTask(int taskId)";
    QSqlQuery query;
    Task task;
    qDebug()<<"get task called with task id of "<<taskId;
    query.prepare(R"(
        SELECT taskId, name, description, complete FROM tasks WHERE taskId = :taskId LIMIT 1)");
    query.bindValue(":taskId", taskId);
    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << "Error getting task:" << query.lastError().text();
        task.name = "could not select a task due to sql problems";
        return task;
    }


    if(query.first()){
        QString taskName = query.value(1).toString();
        QString taskDescription = query.value(2).toString();
        bool complete = query.value(3).toBool();
        qDebug()<<"task desc: "<<taskDescription;
        task.taskId = taskId;
        task.name = taskName;
        task.description = taskDescription;
        task.completed = complete;
    } else {
        qDebug()<<"ccouldnt query.first() "<<query.lastError().text();
    }

    return task;
}

//tasks
QList<Task> Database::getTasksByThread(int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"getTasksByThreadId(int threadId)";
    qDebug()<<"get tasks by thread called with a thread id of "<<threadId;
    QList<Task> noTasks;
    if (!(threadId >=0 )) return noTasks;
    QSqlQuery query;
    QList<Task> tasks;
    query.prepare(R"(
        SELECT taskId, name, description, complete FROM tasks WHERE threadId = :threadId
    )");
    query.bindValue(":threadId", threadId);
    if (!query.exec()) {
            qDebug() <<"error getting all threads: "<<query.lastError();
            return tasks;
        }
    while(query.next()){

        int taskId = query.value(0).toInt();
        QString taskName = query.value(1).toString();
        QString taskDescription = query.value(2).toString();
        bool complete = query.value(3).toBool();
        qDebug()<<"task name: "<<taskName;
        qDebug()<<"task description: "<<taskDescription;
        Task task;
        task.taskId = taskId;
        task.name = taskName;
        task.description = taskDescription;
        task.completed = complete;
        task.threadId = threadId;
        tasks.append(task);
    }
    return tasks;
}

// threads
Thread Database::getThread(int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"getThread(int threadId)";
    QSqlQuery query;
    query.prepare(R"(
        SELECT threadName, isArchived FROM threads WHERE threadId = :threadId)");
    query.bindValue(":threadId",threadId);

    if (!query.exec()) {
        qDebug() << "Error getting thread:" << query.lastError();
        Thread thread;
        return thread;
    }

    QString threadName = query.value(0).toString();
    bool isArchived = query.value(2).toBool();
    Thread thread;
    thread.name = threadName;
    thread.archived = isArchived;
    thread.threadId = threadId;
    return thread;
}

// threads
QList<Thread> Database::getAllThreads()
{
    qDebug()<<"---------Database------------";
    qDebug()<<"getAllThreadds()";
    QSqlQuery query;
    QList<Thread> threads;
    query.prepare(R"(
        SELECT threadId, threadName, isArchived FROM threads
    )");
    if (!query.exec()) {
            qDebug() <<"error getting all threads: "<<query.lastError();
            return threads;
        }
    while(query.next()){
        int threadId = query.value(0).toInt();
        QString threadName = query.value(1).toString();
        bool isArchived = query.value(2).toBool();
        qDebug()<<"isArchived: "<<isArchived<<" for "<<threadName;
        Thread thread;
        thread.name = threadName;
        thread.archived = isArchived;
        thread.threadId = threadId;
        threads.append(thread);
        qDebug() << "found thread: "<< thread.name;
    }
    return threads;
}

// threads
bool Database::isAllComplete(int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"isAllComplete(int threadId)";
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            COUNT(*) AS total,
            SUM(CASE WHEN completed = 1 THEN 1 ELSE 0 END) AS completed
        FROM tasks
        WHERE threadId = :threadId
    )");

    query.bindValue(":threadId",threadId);

    if (!query.exec() || !query.next())
        return false;

    int total = query.value(0).toInt();
    int completed = query.value(1).toInt();
    qDebug()<<"all tasks: "<<total<<" complete tasks: "<<completed;
    return total > 0 && total == completed;
}

// threads
bool Database::Archive(int threadId)
{
    qDebug()<<"---------Database------------";
    qDebug()<<"archive(int threadId)";
    QSqlQuery query;
    if(isAllComplete(threadId)){
        query.prepare(R"(
        UPDATE threads SET isArchived = true WHERE threadId = :threadId)");
        query.bindValue(":threadId", threadId);
    } else {
        return false;
    }
    return query.exec();
}



//db
bool Database::wipe()
{
    qDebug()<<"---------Database------------";
    qDebug()<<"wipe()";
    QSqlQuery query;
    query.prepare(R"(
        DELETE FROM tasks
        DELETE FROM threads)");
    return query.exec();
}