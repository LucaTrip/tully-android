#include <QNetworkReply>
#include <QProcessEnvironment>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QMap>
#include <QDebug>

#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
  , m_manager { new QNetworkAccessManager }
{
    //facendo così le chiamate diventano asincrone e il segnale finished ha la reply che poi passeremo allo slot replyFinished
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void Client::getJsonData()
{
    auto env = QProcessEnvironment::systemEnvironment();
    QUrl url(env.value("TULLY_BACKEND_URL"));
    url.setUserName(env.value("TULLY_BACKEND_USERNAME"));
    url.setPassword(env.value("TULLY_BACKEND_PASSWORD"));
    m_manager->get(QNetworkRequest(url));

}

void Client::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Failure -> " << reply->errorString();
        reply->deleteLater();
        return;
    }

    auto jsonDocument = QJsonDocument::fromJson(reply->readAll());
    auto jsonObject = jsonDocument.object();
    auto results = jsonObject.value("results").toArray().at(0).toObject();
    auto variantMap = results.toVariantMap();
    //rimuoviamo i due valori che non ci servono
    variantMap.remove("id");
    variantMap.remove("created");

    emit mapReady(variantMap);
}
