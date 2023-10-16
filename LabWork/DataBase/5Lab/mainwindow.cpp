#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /*
    foreach (QString driver, QSqlDatabase::drivers ())
    {
        qDebug() << driver;
    }
    */

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./equipmentDB.db");

    if (!db.open())
    {
        qDebug("noOpen");
        QMessageBox::information(this,"","Не вдалось відкрити базу даних");
        return;
    }

    query = new QSqlQuery(db);
    //query->exec("your sql-query :-)");

    tableModel = new QSqlTableModel(this, db);
    tableModel->setTable("Завдання");
    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        tableModel->setTable("Завдання");
        tableModel->select();

        ui->tableView->setModel(tableModel);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 1)
    {
        tableModel->setTable("Виконує_завдання");
        tableModel->select();

        ui->tableView_2->setModel(tableModel);
        ui->tableView_2->resizeColumnsToContents();
        ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 2)
    {
        tableModel->setTable("Обладнання");
        tableModel->select();

        ui->tableView_3->setModel(tableModel);
        ui->tableView_3->resizeColumnsToContents();
        ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 3)
    {
        tableModel->setTable("Використовує");
        tableModel->select();

        ui->tableView_4->setModel(tableModel);
        ui->tableView_4->resizeColumnsToContents();
        ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 4)
    {
        tableModel->setTable("Працівник");
        tableModel->select();

        ui->tableView_5->setModel(tableModel);
        ui->tableView_5->resizeColumnsToContents();
        ui->tableView_5->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 5)
    {
        tableModel->setTable("Інструмент");
        tableModel->select();

        ui->tableView_6->setModel(tableModel);
        ui->tableView_6->resizeColumnsToContents();
        ui->tableView_6->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 6)
    {
        tableModel->setTable("Підвищує_кваліфікацію");
        tableModel->select();

        ui->tableView_7->setModel(tableModel);
        ui->tableView_7->resizeColumnsToContents();
        ui->tableView_7->horizontalHeader()->setStretchLastSection(true);
    }
    else if(index == 7)
    {
        tableModel->setTable("Кваліфікація");
        tableModel->select();

        ui->tableView_8->setModel(tableModel);
        ui->tableView_8->resizeColumnsToContents();
        ui->tableView_8->horizontalHeader()->setStretchLastSection(true);
    }
    else if(index == 8)
    {
        tableModel->setTable("Тип_навчання");
        tableModel->select();

        ui->tableView_9->setModel(tableModel);
        ui->tableView_9->resizeColumnsToContents();
        ui->tableView_9->horizontalHeader()->setStretchLastSection(true);
    }
    else
    {
        QMessageBox::information(this,"","Помилка завантаження таблиці");
    }
}

