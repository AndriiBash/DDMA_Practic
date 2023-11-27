#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>

#include "addrowform.h"

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_AddNew_triggered();

    void on_DeleteRow_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void printDocumentToPDF(const QString path, const QString html);

    QString getHeaderHTML();

    void on_report_triggered();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *tableModel;
    QSqlTableModel *secondTableModel;
    QSqlQueryModel *queryModel;

    int row;

    bool isTableChoose;

    AddRowForm *showFormAdd;

public slots:
    void slotSetData(QString lastName, QString name, QString fatherName, int year, QString post);


};
#endif // MAINWINDOW_H
