#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Моя база даних");

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

    secondTableModel = new QSqlTableModel(this, db);

    queryModel = new QSqlQueryModel();

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

        tableModel->insertRow(tableModel->rowCount());

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
    else if (index == 7)
    {
        tableModel->setTable("Кваліфікація");
        tableModel->select();

        ui->tableView_8->setModel(tableModel);
        ui->tableView_8->resizeColumnsToContents();
        ui->tableView_8->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 8)
    {
        tableModel->setTable("Тип_навчання");
        tableModel->select();

        ui->tableView_9->setModel(tableModel);
        ui->tableView_9->resizeColumnsToContents();
        ui->tableView_9->horizontalHeader()->setStretchLastSection(true);
    }
    else if (index == 9)
    {
        tableModel->setTable("Працівник");
        tableModel->select();

        secondTableModel->setTable("Використовує");
        secondTableModel->select();

        ui->tableView_10->setModel(tableModel);
        ui->tableView_11->setModel(secondTableModel);

    }
    else if (index == 10) {}
    else
    {
        QMessageBox::information(this,"","Помилка завантаження таблиці");
    }
}


void MainWindow::on_tableView_10_clicked(const QModelIndex &index)
{
    secondTableModel->setFilter("Табельний_номер_працівника = " + QString::number(index.row() + 1) + "");
}


void MainWindow::on_pushButton_clicked()
{
    queryModel->setQuery("SELECT Завдання.*, Виконує_завдання.Кількість_годин_роботи "
                         "FROM Завдання, Виконує_завдання "
                         "WHERE Виконує_завдання.Кількість_годин_роботи = (SELECT MIN(Виконує_завдання.Кількість_годин_роботи)"
                         "                                                 FROM Виконує_завдання) "
                         "AND Завдання.Номер_завдання = Виконує_завдання.Номер_виконання");

    ui->sqlTableView->setModel(queryModel);
}


void MainWindow::on_pushButton_2_clicked()
{
    QStringList items;

    if (query->exec("SELECT DISTINCT Працівник.Посада"
                    " FROM Працівник"))
    {
        while (query->next())
        {
            QString position = query->value(0).toString();
            items.append(position);
        }
    }

    bool ok;
    QString selectedItem = QInputDialog::getItem(nullptr, "2 запит", "Оберіть посаду:", items, 0, false, &ok);

    if (ok)
    {
        queryModel->setQuery("SELECT Працівник.*, COUNT(Використовує.Табельний_номер_працівника) AS 'Кількість використання обладнання' "
                             "FROM Працівник "
                             "LEFT JOIN Використовує ON Працівник.Табельний_номер = Використовує.Табельний_номер_працівника "
                             "WHERE Працівник.Посада = '" + selectedItem + "' "
                             "GROUP BY Використовує.Табельний_номер_працівника");

        ui->sqlTableView->setModel(queryModel);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    queryModel->setQuery("SELECT Працівник.*, Підвищує_кваліфікацію.Результат_навчання "
                         "FROM Працівник, Підвищує_кваліфікацію "
                         "WHERE Працівник.Табельний_номер = Підвищує_кваліфікацію.Табельний_номер_працівника "
                         "AND Підвищує_кваліфікацію.Результат_навчання = 'Не пройшов'");

    ui->sqlTableView->setModel(queryModel);

}

