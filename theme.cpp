#include "theme.h"

Theme::Theme()
{

}

QString Theme::getThemesPath()
{
    // Points to a "themes" folder next to the app executable
    // (Or use QStandardPaths::AppConfigLocation for user-installed themes)
    QDir dir(QCoreApplication::applicationDirPath());
    dir.mkdir("themes"); // Create if it doesn't exist
    return dir.absoluteFilePath("themes");
}

QStringList Theme::getAvailableThemes()
{
    QDir themesDir(getThemesPath());

    // Filter for .qss files
    QStringList filters;
    filters << "*.qss";


    // Returns list of filenames like ("Dark.qss", "Nord.qss")
    return themesDir.entryList(filters, QDir::Files);
}