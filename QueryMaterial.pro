QT       += core gui sql

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

SOURCES += \
    conn.cpp \
    main.cpp \
    home.cpp

HEADERS += \
    conn.h \
    home.h

FORMS += \
    home.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = 2254.ico

VERSION = 1.12.65.1

QMAKE_TARGET_COMPANY = GitHub Inc.
QMAKE_TARGET_PRODUCT = Qt5 GUI App
QMAKE_TARGET_DESCRIPTION = Jednostavna aplikacija za rad sa lokalnom bazom podataka preko upita.
QMAKE_TARGET_COPYRIGHT = 2020. Danijel Jovanovic | Podrzi projekte otvorenog koda!
