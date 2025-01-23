#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

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
    QString fileName = QFileDialog::getOpenFileName(this, "Відкрити файл", "", "Text Files (*.txt);;All Files (*)");

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
    }
}


void MainWindow::on_action_triggered()
{
    ui->textEdit->selectAll();
}


void MainWindow::on_pushButton_2_clicked()
{
    bool toolbarVisible = ui->menubar->isEnabled();

    if (toolbarVisible)
    {
        ui->pushButton_2->setText("Показати панель інструментів");
        ui->menubar->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setText("Сховати панель інструментів");
        ui->menubar->setEnabled(true);
    }
}

