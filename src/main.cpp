#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "facelogger.h"
#include "facereader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<FaceLogger>("an.qt.FaceLogger", 1, 0, "FaceLogger");
    FaceLogger *m = new FaceLogger;
    engine.rootContext()->setContextProperty("FaceLogger", m);
    engine.addImageProvider(QLatin1String("FaceLogger"), m);

    qmlRegisterType<FaceLogger>("an.qt.FaceReader", 1, 0, "FaceReader");
    FaceReader *r = new FaceReader;
    engine.rootContext()->setContextProperty("FaceReader", r);
    engine.addImageProvider(QLatin1String("FaceReader"), r);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
