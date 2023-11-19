#include "addrowform.h"
#include "ui_addrowform.h"

#include <QMessageBox>

AddRowForm::AddRowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRowForm)
{
    ui->setupUi(this);

    setWindowTitle("Додати працівника");
}

AddRowForm::~AddRowForm()
{
    delete ui;
}

void AddRowForm::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
       ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() ||
        ui->lineEdit_5->text().isEmpty())
    {
        QMessageBox::information(this,"","Всі поля повині бути заповнені!");
    }
    else
    {

        emit signalSetData(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                           ui->lineEdit_4->text().toInt(), ui->lineEdit_5->text());
    }

}

