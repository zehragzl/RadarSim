#include <QApplication>
#include <QMetaObject>
#include "ui/RadarWidget.h"
#include "core/ObjectManager.h"
#include "core/SimulationEngine.h"
#include "radar/IFFSystem.h"
#include "radar/Radar.h"
#include "radar/ThreatAnalyzer.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ObjectManager manager;
    SimulationEngine engine(manager);
    RadarWidget radar;

    // IFF atamaları
    IFFSystem iff;
    iff.setStatus(1,  IFFStatus::FOE);
    iff.setStatus(2,  IFFStatus::FRIEND);
    iff.setStatus(3,  IFFStatus::FOE);
    iff.setStatus(4,  IFFStatus::FRIEND);
    iff.setStatus(5,  IFFStatus::FOE);
    iff.setStatus(6,  IFFStatus::FRIEND);
    iff.setStatus(7,  IFFStatus::FOE);
    iff.setStatus(8,  IFFStatus::FRIEND);
    iff.setStatus(9,  IFFStatus::FOE);
    iff.setStatus(10, IFFStatus::FRIEND);
    iff.setStatus(11, IFFStatus::FOE);
    iff.setStatus(12, IFFStatus::FRIEND);
    iff.setStatus(13, IFFStatus::FRIEND);
    iff.setStatus(14, IFFStatus::FRIEND);
    // 15-50 arası UNKNOWN (kayıtlı değil → varsayılan)

    Radar radarSensor(250.0, 0.005);
    ThreatAnalyzer analyzer(250.0);

    radar.setFixedSize(800, 800);
    radar.setWindowTitle("RadarSim");

    engine.setOnSnapshot([&]() {
        auto objects = manager.getObjects();
        radarSensor.scan(objects, iff);
        auto tracks  = radarSensor.getTracks();
        auto reports = analyzer.analyzeAll(tracks);

        QMetaObject::invokeMethod(&radar, [&radar, tracks, reports]() {
            radar.setTracks(tracks, reports);
        }, Qt::QueuedConnection);
    });

    QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
        engine.stop();
    });

    engine.start();
    radar.show();
    return app.exec();
}
