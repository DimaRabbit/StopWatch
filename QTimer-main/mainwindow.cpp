#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), stopwatch(new Stopwatch(this)) {
    ui->setupUi(this);

    connect(stopwatch, &Stopwatch::timeUpdated, this, [this](const QString& time) {
        ui->lblTime->setText(time);
    });

    connect(ui->btnStartStop, &QPushButton::clicked, this, [this]() {
        if (ui->btnStartStop->text() == "Старт") {
            stopwatch->start();
            ui->btnStartStop->setText("Стоп");
            ui->btnLap->setEnabled(true);
        } else {
            stopwatch->stop();
            ui->btnStartStop->setText("Старт");
            ui->btnLap->setEnabled(false);
        }
    });

    connect(ui->btnReset, &QPushButton::clicked, this, [this]() {
        stopwatch->reset();
        ui->txtBrowser->clear();

        if (ui->btnStartStop->text() == "Стоп") {
            stopwatch->start();
        }
    });

    connect(ui->btnLap, &QPushButton::clicked, this, [this]() {
        QString lapTime = stopwatch->getLapTime();
        QString totalLapTime = stopwatch->getTime();
        ui->txtBrowser->append(QString("Круг %1: Время круга: %2, Общее время: %3")
                                   .arg(ui->txtBrowser->document()->blockCount() + 1)
                                   .arg(lapTime)
                                   .arg(totalLapTime));
    });

    ui->btnLap->setEnabled(false);  // Кнопка "Круг" изначально отключена
}

MainWindow::~MainWindow() {
    delete ui;
    delete stopwatch;
}
