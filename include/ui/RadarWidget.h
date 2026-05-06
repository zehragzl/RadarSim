#ifndef RADARWIDGET_H
#define RADARWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <unordered_map>

#include "../radar/Track.h"
#include "../radar/ThreatAnalyzer.h"
#include "../core/Vector2D.h"

class RadarWidget : public QWidget {
    Q_OBJECT

public:
    explicit RadarWidget(QWidget* parent = nullptr);

    void setTracks(const std::vector<Track>& tracks,
                   const std::vector<ThreatReport>& reports,
                   const std::unordered_map<int, std::vector<Vector2D>>& predictions = {});

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    std::vector<Track> tracks_;
    std::vector<ThreatReport> reports_;
    std::unordered_map<int, std::vector<Vector2D>> predictions_;
    double sweepAngle_;
    double rangeKm_;
    bool blinkOn_;
    QTimer* timer_;

    QPointF worldToScreen(const Vector2D& pos) const;
    void drawGrid(QPainter& painter);
    void drawSweep(QPainter& painter);
    void drawTargets(QPainter& painter);
    void drawPredictions(QPainter& painter);
    QColor iffColor(IFFStatus iff) const;

private slots:
    void onTick();
};

#endif
