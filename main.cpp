#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "one_at_a_time_please_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    QCoreApplication::setOrganizationName("Vieie");
    QCoreApplication::setApplicationName("One at a time please");
    QSettings settings;
    // set default language
    if(!settings.contains("language")){
        QStringList locales = QLocale::system().uiLanguages();
        for(const QString &locale : locales){
            const QString baseName = QLocale(locale).name();
            settings.setValue("language", baseName);
        }
    }
    // set default theme
    if(!settings.contains("theme")){
        settings.setValue("theme", "Light");
    }
    MainWindow w;
    w.show();
    return QApplication::exec();
}
