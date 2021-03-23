#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T15:14:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = accounting_Beta2
TEMPLATE = app


SOURCES += main.cpp\
    barchart.cpp \
    donutchart.cpp \
    chart.cpp \
    accounting.cpp \
    accountstatement.cpp \
    editpage.cpp \
    budget.cpp \
    homepage.cpp \
    homepage_1.cpp \
    setting_2.cpp \
    setting.cpp

HEADERS  +=barChart.h \
    donutChart.h \
    chart.h \
    accounting.h \
    accountstatement.h \
    editpage.h \
    budget.h \
    homepage.h \
    homepage_1.h \
    setting_2.h \
    setting.h

FORMS    +=chart.ui \
    accounting.ui \
    accountstatement.ui \
    editpage.ui \
    homepage.ui \
    budget.ui \
    homepage_1.ui \
    setting_2.ui \
    setting.ui

RESOURCES += \
    img.qrc

DISTFILES +=
