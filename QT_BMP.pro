QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mw.cpp \
    mypicture.cpp \
    pixeltable.cpp \
    secondwindow.cpp \
    vectorwindow.cpp

HEADERS += \
    mw.h \
    mypicture.h \
    pixeltable.h \
    secondwindow.h \
    vectorwindow.h

FORMS += \
    mw.ui \
    secondwindow.ui \
    vectorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
