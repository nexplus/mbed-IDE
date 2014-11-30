#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include "ServerLinkManager.h"


#define AUTHENTICATION_LOGIN_AND_PASSWORD_FILENAME tr("auth_cache.txt")

enum AuthenticationState { AuthenticationNotInProgress, AuthenticationInProgress, AuthenticationSuccessed};
enum AuthenticationRequestStage{ AuthenticationRequestStageFinished, AuthenticationRequestStageGettingSalt, AuthenticationRequestStageGettingCookies};

class AuthenticationManager : public QObject
{
    Q_OBJECT

public:
    static AuthenticationManager* sharedObject();

    AuthenticationManager(QObject *parent = 0);

    void tryToAuthenticate(QString _login, QString _password);

    AuthenticationState authenticationState();

signals:
    void authenticationResultReceived(QString data);

public slots:
    void requestResponseRecevied(QString response, QList<QNetworkReply::RawHeaderPair>  headersList);

protected:
    QString csrfTokenCookie, developerSessionIdCookie;
    QString login, password;

    enum AuthenticationState currentAuthenticationState;
    enum AuthenticationRequestStage currentAuthenticationRequestStage;
};
