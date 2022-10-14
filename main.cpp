#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>


#include <partie1.h>
#include "partie2.h"
#include "partie3.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Partie2 part2;
    partie3 part3;

    qmlRegisterType<Frame>("com.ProjetComputerVision.frame", 1, 0, "Frame");
    qRegisterMetaType<cv::Mat>("Mat");

    engine.rootContext()->setContextProperty("part2", &part2);
    engine.rootContext()->setContextProperty("part3", &part3);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
