#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T09:00:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MBedIDE
TEMPLATE = app


SOURCES += main.cpp \
    Presentation/EditorWindow.cpp \
    Presentation/TextHighlighter.cpp \
    Presentation/TextLineNumbers.cpp \
    Infrastructure/ServerLinkManager.cpp \
    Infrastructure/WorkspaceFilesManager.cpp \
    Presentation/LoginWindow.cpp \
    Infrastructure/AuthenticationManager.cpp

HEADERS  += \
    Presentation/EditorWindow.h \
    Presentation/TextEditWithLineNumbers.h \
    Presentation/TextHighlighter.h \
    Presentation/TextLineNumbers.h \
    Infrastructure/ServerLinkManager.h \
    Infrastructure/WorkspaceFilesManager.h \
    Presentation/LoginWindow.h \
    Infrastructure/AuthenticationManager.h

RESOURCES += \
    Resources/Resources.qrc
