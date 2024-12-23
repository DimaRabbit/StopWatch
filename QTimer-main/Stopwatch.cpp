#include "Stopwatch.h"
#include <QTime>

Stopwatch::Stopwatch(QObject* parent) : QObject(parent), elapsedTime(0), lastLapTime(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::update);
}

void Stopwatch::start() {
    timer->start(100);  // Обновляем каждые 0.1 секунды
}

void Stopwatch::stop() {
    timer->stop();
}

void Stopwatch::reset() {
    elapsedTime = 0;
    lastLapTime = 0;
    emit timeUpdated("00:00.0");
}

QString Stopwatch::getTime() const {
    qint64 seconds = elapsedTime / 10;
    qint64 milliseconds = elapsedTime % 10;
    return QString("%1:%2.%3")
        .arg(seconds / 60, 2, 10, QChar('0'))
        .arg(seconds % 60, 2, 10, QChar('0'))
        .arg(milliseconds);
}

QString Stopwatch::getLapTime() {
    qint64 lapTime = elapsedTime - lastLapTime;
    lastLapTime = elapsedTime;
    qint64 seconds = lapTime / 10;
    qint64 milliseconds = lapTime % 10;
    return QString("%1:%2.%3")
        .arg(seconds / 60, 2, 10, QChar('0'))
        .arg(seconds % 60, 2, 10, QChar('0'))
        .arg(milliseconds);
}

void Stopwatch::update() {
    elapsedTime++;
    emit timeUpdated(getTime());
}
