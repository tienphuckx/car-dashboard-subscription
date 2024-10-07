#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CarData.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CarData carData;
    engine.rootContext()->setContextProperty("carData", &carData);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("car-dashboard-subscription", "Main");

    return app.exec();
}
