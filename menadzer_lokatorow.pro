#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T20:30:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menadzer_lokatorow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    operacje_na_plikach.cpp \
    okno_dodaj_lokatora.cpp \
    okno_szukaj_lokatora.cpp \
    obsluga_czasu.cpp

HEADERS  += mainwindow.h \
    operacje_na_plikach.h \
    okno_dodaj_lokatora.h \
    okno_szukaj_lokatora.h \
    obsluga_czasu.h


FORMS    += mainwindow.ui \
    okno_dodaj_lokatora.ui \
    okno_szukaj_lokatora.ui
