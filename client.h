#ifndef CLIENT_H
#define CLIENT_H

#include <QNetworkAccessManager>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = Q_NULLPTR);
    void getJsonData();

public slots:
    void replyFinished(QNetworkReply *reply);

signals:
    void mapReady(QVariantMap map);

private:
    QNetworkAccessManager *m_manager;

};

#endif // CLIENT_H
