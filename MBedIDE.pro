#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T09:00:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MBedIDE
TEMPLATE = app


SOURCES += main.cpp \
    Presentation/EditorWindow.cpp \
    Presentation/TextHighlighter.cpp \
    Presentation/TextLineNumbers.cpp

HEADERS  += \
    Presentation/EditorWindow.h \
    Presentation/TextEditWithLineNumbers.h \
    Presentation/TextHighlighter.h \
    Presentation/TextLineNumbers.h

RESOURCES += \
    Resources/Resources.qrc
