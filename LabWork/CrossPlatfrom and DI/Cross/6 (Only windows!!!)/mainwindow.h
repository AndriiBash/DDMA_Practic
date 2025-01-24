#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QAxWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QString>

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
    void on_openTable_clicked();

    void on_calculate_clicked();

private:
    Ui::MainWindow *ui;

    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheet;

    QString fileName;
};
#endif // MAINWINDOW_H
