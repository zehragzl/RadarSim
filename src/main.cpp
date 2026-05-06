#include <QApplication>
#include <QMetaObject>
#include <unordered_map>
#include "ui/RadarWidget.h"
#include "core/ObjectManager.h"
#include "core/SimulationEngine.h"
#include "core/ScenarioLoader.h"
#include "radar/IFFSystem.h"
#include "radar/Radar.h"
#include "radar/ThreatAnalyzer.h"
#include "radar/TrackPredictor.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ObjectManager manager;
    IFFSystem iff;

    ScenarioLoader::load(SCENARIOS_DIR "/default.json", manager, iff);

    SimulationEngine engine(manager);
    RadarWidget radar;

    Radar radarSensor(250.0, 0.005);
    ThreatAnalyzer analyzer(250.0);
    TrackPredictor predictor;

    radar.setFixedSize(800, 800);
    radar.setWindowTitle("RadarSim");

    engine.setOnSnapshot([&]() {
        auto objects = manager.getObjects();
        radarSensor.scan(objects, iff);
        auto tracks  = radarSensor.getTracks();
        auto reports = analyzer.analyzeAll(tracks);

        predictor.update(tracks);
        std::unordered_map<int, std::vector<Vector2D>> predictions;
        for (const auto& t : tracks)
            predictions[t.id] = predictor.predict(t.id);

        QMetaObject::invokeMethod(&radar, [&radar, tracks, reports, predictions]() {
            radar.setTracks(tracks, reports, predictions);
        }, Qt::QueuedConnection);
    });

    QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
        engine.stop();
    });

    engine.start();
    radar.show();
    return app.exec();
}
