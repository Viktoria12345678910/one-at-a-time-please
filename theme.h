#ifndef THEME_H
#define THEME_H
#include "imports.h"


class Theme
{
public:
    Theme();
    QString getThemesPath();
    QStringList getAvailableThemes();
};

#endif // THEME_H
