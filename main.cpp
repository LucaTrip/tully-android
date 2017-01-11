#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QVariant>

#include "datamodel.h"
#include "client.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<DataModel>();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto model = new DataModel();
    auto client = new Client();

    QObject::connect(client, SIGNAL(mapReady(QVariantMap)), model, SLOT(mapReceived(QVariantMap)));

    auto timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, client, &Client::getJsonData);
    timer->start(1000);

    auto *context = engine.rootContext();
    context->setContextProperty("dataModel", QVariant::fromValue(model));

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
