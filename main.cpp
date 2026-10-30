#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QCoreApplication::setOrganizationName("Vieie");
    QCoreApplication::setApplicationName("One at a time please");
    QSettings settings;

    if(!settings.contains("language")){
        QStringList locales = QLocale::system().uiLanguages();
    }

    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "one_at_a_time_please_" + settings.value("language").toString();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // set default language

    MainWindow w;
    w.show();
    return QApplication::exec();
}
