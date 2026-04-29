#ifndef RADARWIDGET_H
#define RADARWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>

#include "../domain/FlyingObject.h"

class RadarWidget : public QWidget {
    Q_OBJECT

    public:
        explicit RadarWidget(QWidget* parent = nullptr);
        void setObjects(const std::vector<FlyingObject*>& objects);
        void setSweepAngle(double angle);
    
    protected:
        void paintEvent(QPaintEvent* event) override;
        void resizeEvent(QResizeEvent* event) override;

    private:
        std::vector<FlyingObject*> objects_;
        double sweepAngle_;
        double rangeKm_;
        QTimer* timer_;

        QPointF worldToScreen(const Vector2D& pos) const;
        void drawGrid(QPainter& painter);
        void drawSweep(QPainter& painter);
        void drawTargets(QPainter& painter);
    
    private slots:
        void onTick();


};
#endif