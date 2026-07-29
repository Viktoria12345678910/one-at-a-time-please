#pragma once

#include <QString>

struct Task
{
    int taskId;
    int threadId;
    bool current;

    QString name;
    QString description;

    bool completed;
};