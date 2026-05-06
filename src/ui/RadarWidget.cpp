#include "../../include/ui/RadarWidget.h"

#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QTimer>
#include <algorithm>
#include <cmath>

RadarWidget::RadarWidget(QWidget* parent)
    : QWidget(parent), sweepAngle_(0.0), rangeKm_(250.0), blinkOn_(false)
{
    setMinimumSize(200, 200);
    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_, &QTimer::timeout, this, &RadarWidget::onTick);
    timer_->start();
}

void RadarWidget::setTracks(const std::vector<Track>& tracks,
                             const std::vector<ThreatReport>& reports,
                             const std::unordered_map<int, std::vector<Vector2D>>& predictions)
{
    tracks_      = tracks;
    reports_     = reports;
    predictions_ = predictions;
    update();
}

void RadarWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), Qt::black);
    drawGrid(painter);
    drawSweep(painter);
    drawPredictions(painter);
    drawTargets(painter);
}

void RadarWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    update();
}

QPointF RadarWidget::worldToScreen(const Vector2D& pos) const {
    double cx = width()  / 2.0;
    double cy = height() / 2.0;
    double scale = std::min(width(), height()) / (2.0 * rangeKm_);
    return QPointF(cx + pos.getX() * scale, cy - pos.getY() * scale);
}

void RadarWidget::drawGrid(QPainter& painter) {
    painter.setPen(QPen(Qt::gray, 1));
    double step = 50.0;
    for (double r = step; r <= rangeKm_; r += step) {
        double radius = (r / rangeKm_) * std::min(width(), height()) / 2.0;
        painter.drawEllipse(QPointF(width() / 2.0, height() / 2.0), radius, radius);
    }
    for (int deg = 0; deg < 360; deg += 30) {
        double rad = qDegreesToRadians((double)deg);
        double radius = std::min(width(), height()) / 2.0;
        QPointF end(width() / 2.0 + radius * std::cos(rad),
                    height() / 2.0 - radius * std::sin(rad));
        painter.drawLine(QPointF(width() / 2.0, height() / 2.0), end);
    }
}

void RadarWidget::drawSweep(QPainter& painter) {
    double radius = std::min(width(), height()) / 2.0;
    double maxTrail = 30.0;
    for (double offset = 2.0; offset <= maxTrail; offset++) {
        double rad = qDegreesToRadians(sweepAngle_ - offset);
        QPointF end(width() / 2.0 + radius * std::cos(rad),
                    height() / 2.0 - radius * std::sin(rad));
        int alpha = static_cast<int>(255 * (1.0 - offset / maxTrail));
        painter.setPen(QPen(QColor(0, 255, 0, alpha), 2));
        painter.drawLine(QPointF(width() / 2.0, height() / 2.0), end);
    }
    double sweepRad = qDegreesToRadians(sweepAngle_);
    QPointF sweepEnd(width() / 2.0 + radius * std::cos(sweepRad),
                     height() / 2.0 - radius * std::sin(sweepRad));
    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(QPointF(width() / 2.0, height() / 2.0), sweepEnd);
}

void RadarWidget::drawTargets(QPainter& painter) {
    const double iconSize = 8.0;
    const double scale = std::min(width(), height()) / (2.0 * rangeKm_);

    for (size_t i = 0; i < tracks_.size(); i++) {
        const Track& track = tracks_[i];
        QPointF center = worldToScreen(track.lastKnownPosition);
        QColor color = iffColor(track.iff);

        // Tehdit halkası — HIGH: turuncu, CRITICAL: yanıp sönen kırmızı
        if (i < reports_.size()) {
            ThreatLevel lvl = reports_[i].level;
            if (lvl == ThreatLevel::CRITICAL && blinkOn_) {
                painter.setPen(QPen(Qt::red, 2));
                painter.setBrush(Qt::NoBrush);
                painter.drawEllipse(center, iconSize + 6, iconSize + 6);
            } else if (lvl == ThreatLevel::HIGH) {
                painter.setPen(QPen(QColor(255, 140, 0), 2));
                painter.setBrush(Qt::NoBrush);
                painter.drawEllipse(center, iconSize + 6, iconSize + 6);
            }
        }

        // İkon
        painter.setPen(QPen(color, 1));
        painter.setBrush(QBrush(color));
        QPainterPath path;

        if (track.typeName == "Aircraft") {
            path.moveTo(0, -iconSize);
            path.lineTo(-iconSize, iconSize);
            path.lineTo(iconSize, iconSize);
            path.closeSubpath();
        } else if (track.typeName == "Helicopter") {
            path.addRect(-iconSize, -iconSize, 2 * iconSize, 2 * iconSize);
        } else {
            path.moveTo(0, -iconSize);
            path.lineTo(iconSize, 0);
            path.lineTo(0, iconSize);
            path.lineTo(-iconSize, 0);
            path.closeSubpath();
        }

        QTransform t;
        t.translate(center.x(), center.y());
        painter.drawPath(t.map(path));
    }

    Q_UNUSED(scale);
}

void RadarWidget::drawPredictions(QPainter& painter) {
    for (const auto& track : tracks_) {
        if (track.iff != IFFStatus::FOE)
            continue;

        auto it = predictions_.find(track.id);
        if (it == predictions_.end() || it->second.empty())
            continue;

        const auto& pts = it->second;
        QPointF prev = worldToScreen(track.lastKnownPosition);

        for (int i = 0; i < static_cast<int>(pts.size()); ++i) {
            int alpha = 255 - static_cast<int>(180.0 * i / static_cast<int>(pts.size()));
            QColor c(255, 60, 60, alpha);
            QPointF cur = worldToScreen(pts[i]);

            painter.setPen(QPen(c, 2, Qt::DashLine));
            painter.drawLine(prev, cur);

            painter.setPen(QPen(c, 1));
            painter.setBrush(QBrush(c));
            painter.drawEllipse(cur, 4.0, 4.0);

            prev = cur;
        }
    }
}

QColor RadarWidget::iffColor(IFFStatus iff) const {
    switch (iff) {
        case IFFStatus::FRIEND:  return QColor(0, 150, 255);
        case IFFStatus::FOE:     return Qt::red;
        case IFFStatus::UNKNOWN: return Qt::yellow;
    }
    return Qt::white;
}

void RadarWidget::onTick() {
    sweepAngle_ += 2.0;
    if (sweepAngle_ >= 360.0)
        sweepAngle_ -= 360.0;

    // Her 10 tick'te bir blink durumu değişir (~500ms)
    static int blinkCounter = 0;
    if (++blinkCounter >= 10) {
        blinkOn_ = !blinkOn_;
        blinkCounter = 0;
    }

    update();
}
