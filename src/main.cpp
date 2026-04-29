#include <QApplication>
#include "ui/RadarWidget.h"
#include "core/SimulationClock.h"
#include "core/ObjectManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ObjectManager manager;
    SimulationClock clock;
    RadarWidget radar;

    radar.setFixedSize(800, 800);
    radar.setWindowTitle("RadarSim");
    radar.setObjects(manager.getObjects());

    QObject::connect(&clock, &SimulationClock::tick, [&](double dt) {
        manager.update(dt);
        radar.setObjects(manager.getObjects());
    });

    clock.start();
    radar.show();
    return app.exec();
}
