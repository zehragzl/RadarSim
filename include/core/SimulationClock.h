#ifndef SIMULATIONCLOCK_H
#define SIMULATIONCLOCK_H

#include <QTimer>
#include <QObject>
#include <QDateTime>
#include <QElapsedTimer>


class SimulationClock: public QObject {
    Q_OBJECT
    private:
        QTimer* timer_;
        qint64 lastTime_;

    signals:
        void tick(double dt);

    public:
        explicit SimulationClock(QObject* parent = nullptr);
        void start();
        void stop();
        bool isRunning() const;

    private slots:
        void onTimeout();
};

#endif