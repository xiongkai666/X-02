QT       += core gui charts axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    Engine/Processing/rhsaccess.cpp \
    Engine/Threads/rhsaccesssubthread.cpp \
    GUI/Widgets/mwaveview.cpp \
    GUI/Windows/controlwindow.cpp \
    main.cpp \

HEADERS += \
    Engine/API/PionwayDLL.h \
    Engine/Processing/SaveManagers/csvfilesave.h \
    Engine/Processing/rhsaccess.h \
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
