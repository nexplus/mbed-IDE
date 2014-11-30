#include "ServerLinkManager.h"
#include <QHBoxLayout>

ServerLinkManager* ServerLinkManager::sharedObject()
{
    static ServerLinkManager *manager = new ServerLinkManager;

    return manager;
}

ServerLinkManager::ServerLinkManager(QObject *parent)  : QObject(parent)
{
    currentRequestState = RequestNone;
    lastNetworkReply = NULL;
    compilerVersion = "1.8.13.1";

    qRegisterMetaType<QList<QNetworkReply::RawHeaderPair> >("QList<QNetworkReply::RawHeaderPair>");

    connect(&networkAccessManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),  this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
}

void ServerLinkManager::sslErrors(QNetworkReply *reply, QList<QSslError> errors)
{
    reply->ignoreSslErrors();
}

RequestState ServerLinkManager::requestState()
{
    return currentRequestState;
}

void ServerLinkManager::sendRequest(QString path, QMap<QString, QString> parameters, bool isSecured, bool isPostMethod, QObject *receiver, QString slotName)
{
    currentRequestState = RequestInProgress;
    _receiver = receiver;
    _slotName = slotName;

    QByteArray formData;
    foreach (QString key, parameters.keys())
        formData += (formData.isEmpty() ? tr("") : tr("&")) + key + tr("=") +  QUrl::toPercentEncoding(parameters[key]);

    QString url = SERVER_URL + path;
    if ((!isPostMethod) && (!formData.isEmpty()))
        url += tr("?") + QString::fromUtf8(formData);

    QNetworkRequest request(url);

    request.setRawHeader("Referer", url.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

    if (isSecured)
    {
        //TODO: cookies
        //request.setRawHeader();
        //request.setHeader(CookieHeader, tr(""));
    }

    lastNetworkReply = isPostMethod ? networkAccessManager.post(request, formData) : networkAccessManager.get(request);
    connect(lastNetworkReply, SIGNAL(finished()),  this, SLOT(httpFinished()));
    connect(lastNetworkReply, SIGNAL(readyRead()),  this, SLOT(httpReadyRead()));
    //connect(reply, SIGNAL(downloadProgress(qint64,qint64)),  this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void ServerLinkManager::httpReadyRead()
{

}

QString ServerLinkManager::getCompilerVersion()
{
    return compilerVersion;
}

void ServerLinkManager::setAuthenticationSessionData(QString csrfToken, QString developerSessionId, QString login, QString password)
{
    csrfTokenCookie = csrfToken;
    developerSessionIdCookie = developerSessionId;
    userLogin = login;
    userPassword = password;
}

void ServerLinkManager::httpFinished()
{
    QList<QNetworkReply::RawHeaderPair>  headersList = lastNetworkReply->rawHeaderPairs();
    QByteArray dataBytesArray = lastNetworkReply->readAll();
    QString data = QString::fromUtf8(dataBytesArray);

    //foreach(QNetworkReply::RawHeaderPair pair, headersList)
    //    qDebug() << pair.first << ": " << pair.second;

    lastNetworkReply->deleteLater();
    currentRequestState = RequestNone;

    QMetaObject::invokeMethod(_receiver, _slotName.toLocal8Bit().data(), Qt::QueuedConnection,Q_ARG(QString,data) ,Q_ARG(QList<QNetworkReply::RawHeaderPair>,headersList));
}
