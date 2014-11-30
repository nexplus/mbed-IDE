#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include <QtNetwork/QtNetwork>

#define SERVER_URL tr("https://developer.mbed.org")

enum RequestState { RequestNone, RequestInProgress};

Q_DECLARE_METATYPE(QList<QNetworkReply::RawHeaderPair>)

class ServerLinkManager : public QObject
{
    Q_OBJECT

public:
    static ServerLinkManager* sharedObject();

    ServerLinkManager(QObject *parent = 0);

    void sendRequest(QString path, QMap<QString, QString> parameters, bool isSecured, bool isPostMethod, QObject *receiver, QString slotName);
    RequestState requestState();

    void setAuthenticationSessionData(QString csrfToken, QString developerSessionId, QString login, QString password);    
    QString getCompilerVersion();

//signals:
//    void requestResponseRecevied(QString response, QList<QNetworkReply::RawHeaderPair>  headersList);

public slots:
    void httpReadyRead();
    void httpFinished();
    void sslErrors(QNetworkReply*,QList<QSslError>);

protected:
    QString csrfTokenCookie, developerSessionIdCookie;
    QString userLogin, userPassword;

    enum RequestState currentRequestState;
    QObject *_receiver;
    QString _slotName;

    QNetworkAccessManager networkAccessManager;
    QNetworkReply *lastNetworkReply;
    //QVector<QString> sentRequests;

    QString compilerVersion;
};
