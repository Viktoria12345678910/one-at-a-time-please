QT += widgets core sql concurrent

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeimgdialog.cpp \
    changelanguagedialog.cpp \
    changethemedialog.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    newtaskdialog.cpp \
    newthreaddialog.cpp \
    pomodorodialog.cpp \
    pomodorosettingsdialog.cpp \
    theme.cpp \
    viewttdialog.cpp

HEADERS += \
    changeimgdialog.h \
    changelanguagedialog.h \
    changethemedialog.h \
    database.h \
    imports.h \
    mainwindow.h \
    models/task.h \
    models/thread.h \
    newtaskdialog.h \
    newthreaddialog.h \
    pomodorodialog.h \
    pomodorosettingsdialog.h \
    theme.h \
    viewttdialog.h

FORMS += \
    changeimgdialog.ui \
    changelanguagedialog.ui \
    changethemedialog.ui \
    mainwindow.ui \
    newtaskdialog.ui \
    newthreaddialog.ui \
    pomodorodialog.ui \
    pomodorosettingsdialog.ui \
    viewttdialog.ui

TRANSLATIONS += Languages/one_at_a_time_please_eng.ts \
                Languages/one_at_a_time_please_ua.ts \
                Languages/one_at_a_time_please_pl.ts
CONFIG += lrelease embed_translations
LRELEASE_DIR = .qm

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lang.qrc
