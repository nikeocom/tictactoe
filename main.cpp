#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "board.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Board>("Ext", 0, 1, "Board");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/tictoctoe/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
