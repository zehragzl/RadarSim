#include "../../include/ui/RadarWidget.h"

#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QTimer>
#include <algorithm>                                                                                                                                                  
#include <cmath>                                                                                                                                                      
                      
RadarWidget::RadarWidget(QWidget* parent) : QWidget(parent), sweepAngle_(0.0), rangeKm_(250.0) {
    setMinimumSize(200, 200);
    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_, &QTimer::timeout, this, &RadarWidget::onTick);
    timer_->start();
}   

void RadarWidget::setObjects(const std::vector<FlyingObject*>& objects) {
    objects_ = objects;
    update();
}

void RadarWidget::setSweepAngle(double angle) {
    sweepAngle_ = std::fmod(angle, 360.0);
    if (sweepAngle_ < 0) {
        sweepAngle_ += 360.0;
    }
    update();
}

void RadarWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), Qt::black);                                                                                                                 
    drawGrid(painter);
    drawSweep(painter);
    drawTargets(painter);
}

void RadarWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    update();
}

QPointF RadarWidget::worldToScreen(const Vector2D& pos) const {
    double centerX = width() / 2.0;
    double centerY = height() / 2.0;
    double scale = std::min(width(), height()) / (2.0 * rangeKm_);
    return QPointF(centerX + pos.getX() * scale, centerY - pos.getY() * scale);
}

void RadarWidget::drawGrid(QPainter& painter) {
    painter.setPen(QPen(Qt::gray, 1));
    double step = 50.0; // Grid step in km
    for (double r = step; r <= rangeKm_; r += step) {
        double radius = (r / rangeKm_) * std::min(width(), height()) / 2.0;
        painter.drawEllipse(QPointF(width() / 2.0, height() / 2.0), radius, radius);
    }
    for(int deg = 0; deg < 360; deg += 30) {
        double angleRad = qDegreesToRadians(deg);
        double radius = std::min(width(), height()) / 2.0;
        QPointF endPoint(width() / 2.0 + radius * std::cos(angleRad), height() / 2.0 - radius * std::sin(angleRad));
        painter.drawLine(QPointF(width() / 2.0, height() / 2.0), endPoint);
    }
}

void RadarWidget::drawSweep(QPainter& painter) {
    double radius = std::min(width(), height()) / 2.0;
    double maxTrail = 30.0;
    for(double trailOffset=2.0; trailOffset <= maxTrail; trailOffset++) {
        double trailAngleRad = qDegreesToRadians(sweepAngle_ - trailOffset);
        QPointF trailEndPoint(width() / 2.0 + radius * std::cos(trailAngleRad), height() / 2.0 - radius * std::sin(trailAngleRad));
        int alpha = static_cast<int>(255 * (1.0 - trailOffset / maxTrail));
        painter.setPen(QPen(QColor(0, 255, 0, alpha), 2));
        painter.drawLine(QPointF(width() / 2.0, height() / 2.0), trailEndPoint);
    }
    double sweepAngleRad = qDegreesToRadians(sweepAngle_);
    QPointF sweepEndPoint(width() / 2.0 + radius * std::cos(sweepAngleRad), height() / 2.0 - radius * std::sin(sweepAngleRad));
    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(QPointF(width() / 2.0, height() / 2.0), sweepEndPoint);
}

void RadarWidget::drawTargets(QPainter& painter) {
    painter.setPen(QPen(Qt::red, 1));
    painter.setBrush(QBrush(Qt::red));
    const double iconSize = 8.0;

    for (const auto& obj : objects_) {
        QPointF center = worldToScreen(obj->position());
        QPainterPath path;

        if (obj->typeName() == "Aircraft") {
            path.moveTo(0, -iconSize);
            path.lineTo(-iconSize, iconSize);
            path.lineTo(iconSize, iconSize);
            path.closeSubpath();
        } else if (obj->typeName() == "Helicopter") {
            path.addRect(-iconSize, -iconSize, 2 * iconSize, 2 * iconSize);
        } else if (obj->typeName() == "UAV") {
            path.moveTo(0, -iconSize);
            path.lineTo(iconSize, 0);
            path.lineTo(0, iconSize);
            path.lineTo(-iconSize, 0);
            path.closeSubpath();
        }

        QTransform transform;
        transform.translate(center.x(), center.y());
        painter.drawPath(transform.map(path));
    }
}

void RadarWidget::onTick() {
    sweepAngle_ += 2.0; // Rotate sweep by 2 degrees per tick
    if (sweepAngle_ >= 360.0) {
        sweepAngle_ -= 360.0;
    }   
    update();
}
