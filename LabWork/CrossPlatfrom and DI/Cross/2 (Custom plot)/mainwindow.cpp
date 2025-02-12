#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qcustomplot.h>
#include <QMessageBox>

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


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "Button clicked, starting graph generation";

    bool ok1, ok2, ok3;

    double start = ui->lineEdit->text().toDouble(&ok1); // Початкове значення
    double end = ui->lineEdit_2->text().toDouble(&ok2); // Кінцеве значення
    int numPoints = ui->lineEdit_3->text().toInt(&ok3); // Кількість точок у таблиці

    // Перевірка на коректність введених даних
    if (!ok1 || !ok2 || !ok3 || numPoints <= 1) {
        QMessageBox::warning(this, "Невірні дані", "Будь ласка, введіть правильні значення.");
        return;
    }

    // Обчислення кроку на основі кількості точок
    double step = (end - start) / (numPoints - 1);

    QVector<double> x, y; // Динамічні масиви для збереження даних
    QStringList lst = {"x", "y"}; // Заголовки колонок для таблиці

    ui->tableWidget->setColumnCount(2); // Встановлення кількості колонок
    ui->tableWidget->setRowCount(0); // Встановлення початкової кількості рядків
    ui->tableWidget->setHorizontalHeaderLabels(lst); // Додавання заголовків колонок

    int row = 0; // Індекс рядка для таблиці

    for (double i = start; i <= end; i += step) {
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

    // Перевірка значень для побудови графіка
    if (x.isEmpty() || y.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Немає даних для побудови графіка.");
        return;
    }

    // Побудова графіка
    ui->widget->clearGraphs(); // Очищення попередніх графіків
    ui->widget->addGraph(); // Додавання нового графіка
    ui->widget->graph(0)->setData(x, y); // Прив'язка даних до графіка

    // Встановлення підписів осей
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    // Визначення діапазону осей
    double minY = *std::min_element(y.begin(), y.end());
    double maxY = *std::max_element(y.begin(), y.end());
    qDebug() << "y range:" << minY << "to" << maxY;
    ui->widget->yAxis->setRange(minY, maxY);

    // Динамічне встановлення діапазону осі x
    ui->widget->xAxis->setRange(start, end);

    // Перемальовування графіка
    ui->widget->replot();

    // Визначення діапазонів зміни знаку на протилежний
    QString signChangeRanges = "Діапазони, де функція змінює знак:\n";
    bool signChanged = false;

    for (int i = 1; i < x.size(); ++i) {
        // Перевірка зміни знака між y[i-1] та y[i]
        if ((y[i-1] > 0 && y[i] < 0) || (y[i-1] < 0 && y[i] > 0)) {
            signChangeRanges += QString("x ∈ [%1, %2]\n").arg(x[i-1]).arg(x[i]);
            signChanged = true;
        }
    }

    // Якщо знайшли діапазони зміни знака
    if (signChanged) {
        QMessageBox::information(this, "Діапазони зміни знака", signChangeRanges);
    } else {
        QMessageBox::information(this, "Зміна знака", "Функція не змінює знак на протилежний у заданому діапазоні.");
    }
}

