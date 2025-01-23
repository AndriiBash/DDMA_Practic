#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;

    player->setAudioOutput(audioOutput);


    // Підключаємо сигнал зміни позиції треку до слоту
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    // Підключаємо сигнал зміни значення слайдера до слоту
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &MainWindow::on_horizontalSlider_sliderMoved);

    // Підключаємо сигнал зміни тривалості треку до слоту
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::setSliderRange);



    isOnTrack = false;
    fileName = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadTrack_clicked()
{
    // Фільтр для музичних файлів
    QString filter = "Музичні файли (*.mp3 *.wav *.flac *.ogg *.m4a);;Усі файли (*.*)";

    // Відкриваємо діалог вибору файлу
    fileName = QFileDialog::getOpenFileName(this,
                                                    "Виберіть музичний файл",
                                                    QDir::homePath(),
                                                    filter);
    // Перевіряємо, чи було обрано файл
    if (fileName.isEmpty()) {
        return;
    }

    // Обробка вибраного файлу
    QFileInfo fileinfo(fileName);
    ui->nameTrack->setText(fileinfo.fileName());

    player->setSource(QUrl::fromLocalFile(fileName));

    // Установлюємо тривалість треку в слайдер
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::setSliderRange);
}


void MainWindow::on_startTrack_clicked()
{
    if (isOnTrack)
    {
        isOnTrack = false;
        ui->startTrack->setText("▶️");

        player->pause();
    }
    else
    {
        isOnTrack = true;
        ui->startTrack->setText("⏸️");

        player->play();
    }
}


// Слот для оновлення слайдера в залежності від позиції треку
void MainWindow::positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);  // Оновлюємо слайдер в залежності від поточної позиції
}

// Слот для зміни позиції треку через слайдер
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);  // Встановлюємо позицію треку відповідно до положення слайдера
}

// Установлюємо діапазон слайдера в залежності від тривалості треку
void MainWindow::setSliderRange(qint64 duration)
{
    ui->horizontalSlider->setRange(0, duration);  // Установлюємо діапазон слайдера від 0 до тривалості треку
}
