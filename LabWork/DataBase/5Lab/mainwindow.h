#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_tableView_10_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *tableModel;
    QSqlTableModel *secondTableModel;

    int row;
};
#endif // MAINWINDOW_H
