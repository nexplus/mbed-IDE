#include "WorkspaceFilesManager.h"
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

WorkspaceFilesManager* WorkspaceFilesManager::sharedObject()
{
    static WorkspaceFilesManager *manager = new WorkspaceFilesManager;

    return manager;
}

WorkspaceFilesManager::WorkspaceFilesManager(QObject *parent)  : QObject(parent)
{
}

void WorkspaceFilesManager::loadProjectsList()
{
    ServerLinkManager::sharedObject()->sendRequest(QString("/compiler/?request=/eNqLT423jU9JTUsszSkBABzxBKU="), QMap<QString, QString>(), true, true, this, "projectsListResultReceived");
}

void WorkspaceFilesManager::loadFilesListInFolder(QString folderPath)
{
   //ServerLinkManager::sharedObject()->sendRequest(QString("/compiler/?request=/eNqLT423jU9JTUsszSkBABzxBKU="), QMap<QString, QString>(), true, true, this, "filesListInFolderResultReceived");
}

 void WorkspaceFilesManager::compileProject(QString projectName)
 {
     //&_theitf_request_id=req56
     ServerLinkManager::sharedObject()->sendRequest(QString("/compiler/?request=/eNqLT423Tc7PLcjMSQUAGPkESg==&board=7&program=%1&download=1").arg(projectName), QMap<QString, QString>(), true, true, this, "projectCompileResultReceived");
 }

/*void WorkspaceFilesManager::sessionConfigsAndHeadersResultReceived(QString, QList<QNetworkReply::RawHeaderPair> headersList)
{
    foreach(QNetworkReply::RawHeaderPair pair, headersList)
        qDebug() << pair.first << ": " << pair.second;
}*/

 void WorkspaceFilesManager::filesListInFolderResultReceived(QString data, QList<QNetworkReply::RawHeaderPair> headersList)
{

 }

 void WorkspaceFilesManager::projectCompileResultReceived(QString data, QList<QNetworkReply::RawHeaderPair> headersList)
 {
     foreach(QNetworkReply::RawHeaderPair pair, headersList)
         qDebug() << pair.first << ": " << pair.second;

     qDebug() << data;
 }

 void WorkspaceFilesManager::projectsListResultReceived(QString data, QList<QNetworkReply::RawHeaderPair> headersList)
 {
     projectsNamesList.clear();

     foreach(QNetworkReply::RawHeaderPair pair, headersList)
         qDebug() << pair.first << ": " << pair.second;


     if (data.length() < 50)
         QMessageBox::critical(NULL, tr("Error"), tr("Error in loading projects list"));
     else
     {
         int lastIndex = 0;
         while (1)
         {
             const QString beginString = "t.setAttributes(";
            int newIndexFrom = data.indexOf(beginString, lastIndex);
            if (newIndexFrom < 0)
                break;
            int newIndexTo = data.indexOf(");", newIndexFrom);
            QString jsonDescription = data.mid(newIndexFrom + beginString.length(), newIndexFrom - newIndexTo);

            QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonDescription.toUtf8());
            QJsonObject jsonObject = jsonResponse.object();
            QString projectName = jsonObject.value("name").toString();
            projectsNamesList.push_back(projectName);

            lastIndex = newIndexTo;
         }
     }

     emit projectsListLoaded();
 }

const QStringList WorkspaceFilesManager::getProjectsList()
{
    return projectsNamesList;
}
