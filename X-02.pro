QT       += core gui charts axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

TRANSLATIONS += lang_English.ts \
                lang_zh_CN.ts

INCLUDEPATH += $$PWD/
INCLUDEPATH += $$PWD/Engine/Processing/
INCLUDEPATH += $$PWD/Engine/Processing/SaveManagers/
INCLUDEPATH += $$PWD/Engine/Threads/
INCLUDEPATH += $$PWD/Engine/API/
INCLUDEPATH += $$PWD/GUI/Dialogs/
INCLUDEPATH += $$PWD/GUI/Widgets/
INCLUDEPATH += $$PWD/GUI/Windows/

SOURCES += \
    Engine/Processing/SaveManagers/csvfilesave.cpp \
    Engine/Processing/XPUInterfaces/impedancereader.cpp \
    Engine/Processing/rhsaccess.cpp \
    Engine/Processing/systemstate.cpp \
    Engine/Threads/rhsaccesssubthread.cpp \
    GUI/Widgets/mwaveview.cpp \
    GUI/Windows/controlwindow.cpp \
    main.cpp \

HEADERS += \
    Engine/API/PionwayDLL.h \
    Engine/Processing/SaveManagers/csvfilesave.h \
    Engine/Processing/XPUInterfaces/impedancereader.h \
    Engine/Processing/rhsaccess.h \
    Engine/Processing/systemstate.h \
    Engine/Threads/rhsaccesssubthread.h \
    GUI/Widgets/mwaveview.h \
    GUI/Windows/controlwindow.h \

FORMS += \
    controlwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/Engine/API/ -lPionway

INCLUDEPATH += $$PWD/Engine/API
DEPENDPATH += $$PWD/Engine/API

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Engine/API/Pionway.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/Engine/API/libPionway.a

RESOURCES += \
    Resources.qrc

DISTFILES +=
