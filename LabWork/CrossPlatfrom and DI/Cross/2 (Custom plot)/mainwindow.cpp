#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool ok1, ok2, ok3;
    double start = ui->lineEdit->text().toDouble(&ok1); // Початкове значення
    double end = ui->lineEdit_2->text().toDouble(&ok2); // Кінцеве значення
    double step = ui->lineEdit_3->text().toDouble(&ok3); // Крок

    // Перевірка на коректність введених даних
    if (!ok1 || !ok2 || !ok3 || step <= 0) {
        return;
    }

    QVector<double> x, y; // Динамічні масиви для збереження даних
    QStringList lst = {"x", "y"}; // Заголовки колонок для таблиці

    ui->tableWidget->setColumnCount(2); // Встановлення кількості колонок
    ui->tableWidget->setRowCount(0); // Встановлення початкової кількості рядків
    ui->tableWidget->setHorizontalHeaderLabels(lst); // Додавання заголовків колонок

    int row = 0; // Індекс рядка для таблиці
    for (double i = start; i < end; i += step) {
        x.append(i); // Додавання значення x до вектора
        double yi = (4 * qPow(i, 2) - 1) / (i + 3); // Розрахунок значення y
        y.append(yi); // Додавання значення y до вектора

        // Додавання нового рядка до таблиці
        ui->tableWidget->insertRow(row);
        QTableWidgetItem* itemX = new QTableWidgetItem(QString::number(i));
        QTableWidgetItem* itemY = new QTableWidgetItem(QString::number(yi));
        ui->tableWidget->setItem(row, 0, itemX); // Запис значення x у таблицю
        ui->tableWidget->setItem(row, 1, itemY); // Запис значення y у таблицю
        row++;
    }

    // Побудова графіка
    ui->widget->clearGraphs(); // Очищення попередніх графіків
    ui->widget->addGraph(); // Додавання нового графіка
    ui->widget->graph(0)->setData(x, y); // Прив’язка даних до графіка

    // Встановлення підписів осей
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    // Динамічне встановлення діапазонів осей
    ui->widget->xAxis->setRange(start, end);
    ui->widget->yAxis->setRange(*std::min_element(y.begin(), y.end()),
                                *std::max_element(y.begin(), y.end()));
    ui->widget->replot(); // Перемальовування графіка
}


