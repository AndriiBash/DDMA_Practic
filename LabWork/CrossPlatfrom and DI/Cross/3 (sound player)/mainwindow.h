#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadTrack_clicked();

    void on_startTrack_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void setSliderRange(qint64 duration);

    void positionChanged(qint64 position);

private:
    Ui::MainWindow *ui;

    bool isOnTrack;
    QString fileName;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
};
#endif // MAINWINDOW_H
