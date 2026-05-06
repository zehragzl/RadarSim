#include <QApplication>
#include <QMetaObject>
#include "ui/RadarWidget.h"
#include "core/ObjectManager.h"
#include "core/SimulationEngine.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ObjectManager manager;
    SimulationEngine engine(manager);
    RadarWidget radar;

    radar.setFixedSize(800, 800);
    radar.setWindowTitle("RadarSim");
    radar.setObjects(manager.getObjects());

    // Worker thread'den UI thread'e güvenli geçiş
    engine.setOnSnapshot([&]() {
        QMetaObject::invokeMethod(&radar, [&]() {
            radar.setObjects(manager.getObjects());
        }, Qt::QueuedConnection);
    });

    QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
        engine.stop();
    });

    engine.start();
    radar.show();
    return app.exec();
}
