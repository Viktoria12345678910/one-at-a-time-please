QT += widgets core sql concurrent

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeimgdialog.cpp \
    changelanguagedialog.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    newtaskdialog.cpp \
    newthreaddialog.cpp \
    pomodorodialog.cpp \
    pomodorosettingsdialog.cpp \
    viewttdialog.cpp

HEADERS += \
    changeimgdialog.h \
    changelanguagedialog.h \
    database.h \
    imports.h \
    mainwindow.h \
    models/task.h \
    models/thread.h \
    newtaskdialog.h \
    newthreaddialog.h \
    pomodorodialog.h \
    pomodorosettingsdialog.h \
    viewttdialog.h

FORMS += \
    changeimgdialog.ui \
    changelanguagedialog.ui \
    mainwindow.ui \
    newtaskdialog.ui \
    newthreaddialog.ui \
    pomodorodialog.ui \
    pomodorosettingsdialog.ui \
    viewttdialog.ui

TRANSLATIONS += Languages/one_at_a_time_please_en_US.ts \
                Languages/one_at_a_time_please_uk_UA.ts \
                Languages/one_at_a_time_please_pl_PL.ts
QM_DIR = $$OUT_PWD/.qm
system(mkdir -p $$QM_DIR)
unix:!macx: LRELEASE_BIN = lrelease
else: LRELEASE_BIN = lrelease

qm_eng.target = $$QM_DIR/one_at_a_time_please_eng.qm
qm_eng.input = Languages/one_at_a_time_please_eng.ts
qm_eng.commands = $$LRELEASE_BIN ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}

qm_ua.target = $$QM_DIR/one_at_a_time_please_ua.qm
qm_ua.input = Languages/one_at_a_time_please_ua.ts
qm_ua.commands = $$LRELEASE_BIN ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}

qm_pl.target = $$QM_DIR/one_at_a_time_please_pl.qm
qm_pl.input = Languages/one_at_a_time_please_pl.ts
qm_pl.commands = $$LRELEASE_BIN ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lang.qrc
