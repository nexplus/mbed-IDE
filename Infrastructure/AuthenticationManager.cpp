#include "AuthenticationManager.h"
#include <QHBoxLayout>

AuthenticationManager* AuthenticationManager::sharedObject()
{
    static AuthenticationManager *manager = new AuthenticationManager;

    return manager;
}

AuthenticationManager::AuthenticationManager(QObject *parent)  : QObject(parent)
{
    currentAuthenticationState = AuthenticationNotInProgress;
    currentAuthenticationRequestStage = AuthenticationRequestStageFinished;
}

void AuthenticationManager::tryToAuthenticate(QString _login, QString _password)
{
    currentAuthenticationState = AuthenticationInProgress;
    currentAuthenticationRequestStage = AuthenticationRequestStageGettingSalt;

    login = _login;
    password = _password;
    csrfTokenCookie = "";
    developerSessionIdCookie = "";

    ServerLinkManager::sharedObject()->sendRequest(QString("/account/login/"), QMap<QString, QString>(), false, false, this, "requestResponseRecevied");
}

void AuthenticationManager::requestResponseRecevied(QString response, QList<QNetworkReply::RawHeaderPair>  headersList)
{
    if (currentAuthenticationState == AuthenticationInProgress)
    {
        if (currentAuthenticationRequestStage == AuthenticationRequestStageGettingSalt)
        {
            QString salt;
            const QString saltFieldName("csrfmiddlewaretoken");
            int fieldNameEndIndex = response.indexOf(saltFieldName, 0, Qt::CaseInsensitive);
            if (fieldNameEndIndex > 0)
            {

                fieldNameEndIndex += saltFieldName.length() + 1;
                int saltBeginIndex = response.indexOf("\'", fieldNameEndIndex) + 1;
                int saltEndIndex = response.indexOf("\'", saltBeginIndex);
                salt = response.mid(saltBeginIndex, saltEndIndex-saltBeginIndex);
                //qDebug() << "SALT: " <<  salt;

                currentAuthenticationRequestStage = AuthenticationRequestStageGettingCookies;

                QMap<QString, QString> parameters;
                parameters["email"] = login;
                parameters["password"] = password;
                parameters["keep_cookie"] = "1";
                parameters["csrfmiddlewaretoken"] = salt;
                ServerLinkManager::sharedObject()->sendRequest(QString("/account/login/"), parameters, false, true, this, "requestResponseRecevied");
            }
            else
                emit authenticationResultReceived(tr("Failed to received authentication salt!"));
        }
        else if (currentAuthenticationRequestStage == AuthenticationRequestStageGettingCookies)
        {
            foreach(QNetworkReply::RawHeaderPair pair, headersList)
                if (pair.first == "Set-Cookie")
                {
                    const QString tokenFieldName("csrftoken");
                    const QString developerSessionIdFieldName("sessionid_developer");

                    QStringList params = QString::fromUtf8(pair.second).split("\n");
                    foreach (QString line, params)
                        if (line.startsWith(tokenFieldName))
                            csrfTokenCookie = line.left(line.indexOf(";")).mid(tokenFieldName.length() + 1);
                        else if (line.startsWith(developerSessionIdFieldName))
                            developerSessionIdCookie = line.left(line.indexOf(";")).mid(developerSessionIdFieldName.length() + 1);

                    break;
                }

            //qDebug()<< csrfTokenCookie;
            //qDebug()<< developerSessionIdCookie;

            QString errorString = QString("Please enter a correct username and password");
            if (response.contains(errorString, Qt::CaseInsensitive))
                emit authenticationResultReceived(errorString);
            else
            {
                ServerLinkManager::sharedObject()->setAuthenticationSessionData(csrfTokenCookie, developerSessionIdCookie, login, password);
                emit authenticationResultReceived("");
            }
        }
    }
}

AuthenticationState AuthenticationManager::authenticationState()
{
    return currentAuthenticationState;
}
