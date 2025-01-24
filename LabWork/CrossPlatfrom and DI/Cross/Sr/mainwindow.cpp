#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    model = new QSqlTableModel(this, db);
    queryModel = new QSqlQueryModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Відкриваємо діалог для вибору файлу бази даних
    QString filePath = QFileDialog::getOpenFileName(this, "Оберіть базу даних", QDir::homePath(), "База даних SQLite (*.db);;Усі файли (*.*)");

    // Перевіряємо, чи був вибраний файл
    if (filePath.isEmpty())
    {
        qDebug() << "Файл не вибрано.";
        return;
    }

    // Встановлюємо вибраний файл як базу даних
    db.setDatabaseName(filePath);

    // Намагаємося відкрити базу даних
    if (db.open())
    {
        qDebug() << "Базу даних успішно відкрито: " << filePath;
        model->setTable("Лікарі");
        model->select();
        ui->tableView->setModel(model);
    }
    else
    {
        qDebug() << "Не вдалося відкрити базу даних: " << filePath;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    // Спливаюче вікно для введення імені лікаря
    bool ok;
    QString idDoctor = QInputDialog::getText(this, "Введіть id лікаря", "id лікаря:", QLineEdit::Normal, "", &ok);

    // Якщо користувач натиснув OK і ввів ім'я
    if (ok && !idDoctor.isEmpty())
    {
        // Спливаюче вікно для введення дати
        QString appointmentDate = QInputDialog::getText(this, "Введіть дату запису", "Дата (yyyy-MM-dd):", QLineEdit::Normal, "", &ok);

        // Якщо користувач ввів дату
        if (ok && !appointmentDate.isEmpty())
        {

            // Створюємо модель для відображення результатів
            queryModel->setQuery(
                "SELECT DISTINCT Пацієнти.* FROM Пацієнти, Лікарі, Поліклініка "
                "WHERE Пацієнти.id = Поліклініка.пацієнт_id "
                "AND Поліклініка.дата_запису = '" + appointmentDate + "'"
                "AND Поліклініка.лікар_id = '" + idDoctor + "'"
                );
            ui->tableView_3->setModel(queryModel);
        }
        else
        {
            QMessageBox::warning(this, "Помилка", "Дата не може бути порожньою.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Помилка", "Ім'я лікаря не може бути порожнім.");
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        model->setTable("Лікарі");
        model->select();

        ui->tableView->setModel(model);
    }
    else if (index == 1)
    {
        model->setTable("Пацієнти");
        model->select();

        ui->tableView_2->setModel(model);
    }
    else if (index == 2)
    {
        model->setTable("Поліклініка");
        model->select();

        ui->tableView_3->setModel(model);
    }
}

