#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->setMaximumHeight(50);

    operation = "+";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    // Отримуємо значення з QLineEdit
    double arg1 = ui->lineEdit->text().toDouble();  // Перше значення
    double arg2 = ui->lineEdit_2->text().toDouble();  // Друге значення

    double result = 0.0;
    QString expression;  // Строка для відображення операції

    // Виконуємо відповідну операцію
    if (operation == "+")
    {
        result = arg1 + arg2;
        expression = QString::number(arg1) + " + " + QString::number(arg2) + " = ";
    }
    else if (operation == "-")
    {
        result = arg1 - arg2;
        expression = QString::number(arg1) + " - " + QString::number(arg2) + " = ";
    }
    else if (operation == "/")
    {
        if (arg2 != 0)  // Перевірка на ділення на нуль
        {
            result = arg1 / arg2;
            expression = QString::number(arg1) + " / " + QString::number(arg2) + " = ";
        }
        else
        {
            ui->label_answer->setText("Помилка: Ділення на нуль");
            return;
        }
    }
    else if (operation == "*")
    {
        result = arg1 * arg2;
        expression = QString::number(arg1) + " * " + QString::number(arg2) + " = ";
    }
    else
    {
        ui->label_answer->setText("Невідома операція");
        return;
    }

    // Додаємо вираз та результат в QTextEdit
    ui->textEdit->append(expression + QString::number(result));

    // Оновлюємо лейбл з результатом
    ui->label_answer->setText("Результат: " + QString::number(result));
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    operation = arg1;
}

