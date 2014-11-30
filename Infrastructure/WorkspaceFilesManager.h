#pragma once

#include <QObject>

#include "ServerLinkManager.h"

class WorkspaceFilesManager : public QObject
{
    Q_OBJECT

public:
    static WorkspaceFilesManager* sharedObject();

    WorkspaceFilesManager(QObject *parent = 0);

    void loadProjectsList();
    void loadFilesListInFolder(QString folderPath);

    void loadFileWithName(QString fileName);
    void saveFileWithName(QString fileName, QString content);
    void compileProject(QString projectName);

    void createFileWithName(QString name, QString projectName, QString content);
    void deleteFileWithName(QString name, QString projectName);
    void renameFileFromTo(QString oldName, QString newName, QString projectName);

    const QStringList getProjectsList();

signals:
    void projectsListLoaded();
    void filesListInFolderLoaded();

    void fileLoaded();
    void fileSaved();
    void projectCompiled();

    void fileRenamed();
    void fileCreated();
    void fileDeleted();

public slots:
    void projectsListResultReceived(QString data, QList<QNetworkReply::RawHeaderPair> headersList);
    void filesListInFolderResultReceived(QString data,QList<QNetworkReply::RawHeaderPair> headersList);
    void projectCompileResultReceived(QString data,QList<QNetworkReply::RawHeaderPair> headersList);
    //void sessionConfigsAndHeadersResultReceived(QString,QList<QNetworkReply::RawHeaderPair> headersList);

protected:
    QStringList projectsNamesList;

};
