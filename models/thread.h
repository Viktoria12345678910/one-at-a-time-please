#pragma once

#include <QString>

struct Thread
{
    int threadId;
    QString name;

    bool archived;
};