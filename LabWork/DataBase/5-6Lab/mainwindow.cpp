#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include <QComboBox>
#include <QPrinter>
#include <QDesktopServices>
#include <QFileDialog>

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

    showFormAdd = new AddRowForm();

    connect(showFormAdd, &AddRowForm::signalSetData, this, &MainWindow::slotSetData);

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

        isTableChoose = true;
    }
    else if (index == 1)
    {
        tableModel->setTable("Виконує_завдання");
        tableModel->select();

        tableModel->insertRow(tableModel->rowCount());

        ui->tableView_2->setModel(tableModel);
        ui->tableView_2->resizeColumnsToContents();
        ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 2)
    {
        tableModel->setTable("Обладнання");
        tableModel->select();

        ui->tableView_3->setModel(tableModel);
        ui->tableView_3->resizeColumnsToContents();
        ui->tableView_3->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 3)
    {
        tableModel->setTable("Використовує");
        tableModel->select();

        ui->tableView_4->setModel(tableModel);
        ui->tableView_4->resizeColumnsToContents();
        ui->tableView_4->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 4)
    {
        tableModel->setTable("Працівник");
        tableModel->select();

        ui->tableView_5->setModel(tableModel);
        ui->tableView_5->resizeColumnsToContents();
        ui->tableView_5->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 5)
    {
        tableModel->setTable("Інструмент");
        tableModel->select();

        ui->tableView_6->setModel(tableModel);
        ui->tableView_6->resizeColumnsToContents();
        ui->tableView_6->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 6)
    {
        tableModel->setTable("Підвищує_кваліфікацію");
        tableModel->select();

        ui->tableView_7->setModel(tableModel);
        ui->tableView_7->resizeColumnsToContents();
        ui->tableView_7->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 7)
    {
        tableModel->setTable("Кваліфікація");
        tableModel->select();

        ui->tableView_8->setModel(tableModel);
        ui->tableView_8->resizeColumnsToContents();
        ui->tableView_8->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 8)
    {
        tableModel->setTable("Тип_навчання");
        tableModel->select();

        ui->tableView_9->setModel(tableModel);
        ui->tableView_9->resizeColumnsToContents();
        ui->tableView_9->horizontalHeader()->setStretchLastSection(true);

        isTableChoose = true;
    }
    else if (index == 9)
    {
        tableModel->setTable("Працівник");
        tableModel->select();

        secondTableModel->setTable("Використовує");
        secondTableModel->select();

        ui->tableView_10->setModel(tableModel);
        ui->tableView_11->setModel(secondTableModel);

        isTableChoose = false;

    }
    else if (index == 10)
    {
        isTableChoose = false;
    }
    else if (index == 11)
    {
        isTableChoose = false;
    }
    else if (index == 12)
    {
        on_pushButton_8_clicked();
        isTableChoose = false;
    }
    else if (index == 13)
    {
        isTableChoose = false;
    }
    else
    {
        QMessageBox::information(this,"","Помилка завантаження таблиці");
        isTableChoose = false;
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
        queryModel->setQuery("SELECT Працівник.*, COUNT(Завдання.Номер_завдання) AS 'Кількість виконаних завдань' "
                             "FROM Працівник "
                             "LEFT JOIN Використовує ON Працівник.Табельний_номер = Використовує.Табельний_номер_працівника "
                             "LEFT JOIN Обладнання ON Використовує.Номер_обладнання = Обладнання.Номер_обладнання "
                             "LEFT JOIN Виконує_завдання ON Обладнання.Номер_обладнання = Виконує_завдання.Номер_обладнання "
                             "LEFT JOIN Завдання ON Виконує_завдання.Номер_завдання = Завдання.Номер_завдання "
                             "WHERE Працівник.Посада = '" + selectedItem + "' AND Працівник.Рік_народження > 1950 AND Завдання.Статус = 'Виконанно'"
                             "GROUP BY Завдання.Номер_завдання");

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


void MainWindow::on_pushButton_4_clicked()
{
    queryModel->setQuery("SELECT * "
                "FROM Працівник");

    ui->tableView_12->setModel(queryModel);
}


void MainWindow::on_pushButton_5_clicked()
{
    bool ok;

    int selectedItem = QInputDialog::getInt(nullptr, "Пошук посади за табельним номером",
     "Оберіть табельний номер:", 1, 1, ui->tableView_12->model()->rowCount(), 1, &ok);

    if (ok)
    {

        query->exec("SELECT Працівник.Посада "
                    "FROM Працівник "
                    "WHERE Працівник.Табельний_номер = " + QString::number(selectedItem));

        if (query->next())
        {
            QString result = query->value(0).toString();
            QMessageBox::information(this, "", "Посада працівника : " + result);
        }
        else
        {
            QMessageBox::information(this, "", "Немає результатів пошуку");
        }
    }

}


void MainWindow::on_AddNew_triggered()
{
    showFormAdd->show();
}


void MainWindow::on_DeleteRow_triggered()
{
    bool ok;
    int value = QInputDialog::getInt(nullptr, "Видалення працівника", "Оберіть табельний номер за яким ви хочете видалити працівника:",
                                         0, 0, tableModel->rowCount() - 1, 1, &ok);

    if (ok)
    {
        tableModel->removeRow(value);
        tableModel->select();
    }
}


void MainWindow::slotSetData(QString lastName, QString name, QString fatherName, int year, QString post)
{
    int rowCount = tableModel->rowCount();

    tableModel->insertRow(rowCount);

    QModelIndex index;

    index = tableModel->index(rowCount, 0);
    tableModel->setData(index, rowCount);

    index = tableModel->index(rowCount, 1);
    tableModel->setData(index, lastName);

    index = tableModel->index(rowCount, 2);
    tableModel->setData(index, name);

    index = tableModel->index(rowCount, 3);
    tableModel->setData(index, fatherName);

    index = tableModel->index(rowCount, 4);
    tableModel->setData(index, year);

    index = tableModel->index(rowCount, 5);
    tableModel->setData(index, post);
}


void MainWindow::on_pushButton_6_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);

    proxyModel->setSourceModel(queryModel);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSortRole(Qt::DisplayRole);

    proxyModel->sort(4, Qt::AscendingOrder);  // Сортування за зростанням

    ui->tableView_12->setModel(proxyModel);
}


void MainWindow::on_pushButton_8_clicked()
{
    queryModel->setQuery("SELECT Інструмент.* "
                         "FROM Інструмент "
                         "ORDER BY Назва_інструмента ASC");

    int rowCount = queryModel->rowCount();
    int columnCount = queryModel->columnCount();

    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(columnCount);

    QStringList headerLabels;
    for (int col = 0; col < columnCount; ++col)
    {
        headerLabels << queryModel->headerData(col, Qt::Horizontal).toString();
    }
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < columnCount; ++col)
        {
            QModelIndex index = queryModel->index(row, col);
            QString value = queryModel->data(index).toString();
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(row, col, item);
        }
    }


    //for column's style's
    for (int i = 0; i < queryModel->rowCount(); i++)
    {
        QComboBox *combo = new QComboBox;
        combo->addItem("Ручний");
        combo->addItem("Електричний");
        combo->addItem("Механичний");

        combo->setCurrentText(queryModel->data(queryModel->index(i, 2)).toString());
        ui->tableWidget->setCellWidget(i, 2, combo);

        QTableWidgetItem *item = new QTableWidgetItem(" ");
        ui->tableWidget->setItem(i, 2, item);
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 3);

        if (item)
        {
            item->setBackground(QColor(Qt::green));
            item->setForeground(QColor(Qt::red));
        }
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

        QTableWidgetItem *item = ui->tableWidget->item(i, 0);

        if (item and i % 2 == 0)
        {
            item->setBackground(QColor(Qt::gray));
        }
        else if(item and i % 2 != 0)
        {
            item->setBackground(QColor(Qt::darkGray));
        }
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    int countParametr = 0;

    QString SQLString;
    SQLString = "SELECT Інструмент.* "
                "FROM Інструмент "
                "WHERE ";

    if (!ui->lineEdit->text().isEmpty())
    {
        SQLString += "Інструмент.Назва_інструмента = '" + ui->lineEdit->text() + "' ";
        countParametr++;
    }

    if (!ui->lineEdit_2->text().isEmpty())
    {
        if (countParametr != 0)
        {
            SQLString += " AND ";
        }

        SQLString += "Інструмент.Тип_інструмента = '" + ui->lineEdit_2->text() + "' ";
        countParametr++;
    }

    if (!ui->lineEdit_3->text().isEmpty())
    {
        if (countParametr != 0)
        {
            SQLString += " AND ";
        }

        SQLString += "Інструмент.Опис_інструмента LIKE '%" + ui->lineEdit_3->text() + "%' ";
        countParametr++;
    }

    queryModel->setQuery(SQLString);
    int rowCount = queryModel->rowCount();
    int columnCount = queryModel->columnCount();

    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(columnCount);

    // Встановлення заголовків стовпців
    QStringList headerLabels;
    for (int col = 0; col < columnCount; ++col)
    {
        headerLabels << queryModel->headerData(col, Qt::Horizontal).toString();
    }
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    // Заповнення QTableWidget результатами запиту
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < columnCount; ++col)
        {
            QModelIndex index = queryModel->index(row, col);
            QString value = queryModel->data(index).toString();
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(row, col, item);
        }
    }


    ui->textEdit->clear();

    for (int row = 0; row < rowCount; ++row)
    {
        QString rowText;
        for (int col = 0; col < columnCount; ++col)
        {
            QModelIndex index = queryModel->index(row, col);
            QString value = queryModel->data(index).toString();

            if (col == 0)
            {
                rowText += ("(" + value + ") - ");
            }
            else
            {
                rowText += value + "; ";
            }
        }
    }
}

void MainWindow::printDocumentToPDF(const QString path, const QString html)
{
    QTextDocument *document = new QTextDocument();
    document->setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setColorMode(QPrinter::Color);
    printer.setResolution(666);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(5, 5, 5, 5), QPageLayout::Millimeter);
    printer.setOutputFileName(path);

    document->setPageSize(QSizeF(920, 1300));
    document->print(&printer);

    QDesktopServices::openUrl(QUrl("file://" + path, QUrl::TolerantMode));

}

QString MainWindow::getHeaderHTML()
{
    QString htmlHeader;

    htmlHeader = "<!DOCTYPE html>\n"
                 "<html>\n"
                 "<head>\n"
                 "<style>"
                 "table {\n width: 100%;\n padding-top: 120px;\n}\n"
                 "table, th, td {\n"
                 "  border:1px solid #e8e8e8;\n"
                 "  border-collapse: collapse;\n"
                 "  padding: 3px;\n"
                 "  font-size: 12px;\n"
                 "  font-family: -apple-system, BlinkMacSystemFont, sans-serif;\n"
                 "  background-color: white;\n"
                 "  padding-top: 6px;\n"
                 "  padding-bottom: 6px;\n}\n"
                 "th {\n    color: white;\n"
                 "  background-color: #0e4870;\n"
                 "  text-align: left;\n}\n"
                 "td.la {\n background-color: #f2f2f2;\n}\n"
                 "td.info {\n   border: 0px;\n  background-color: #e1e1e1;\n}\n"
                 "h1, h2, h3 ,h4{\n font-family: -apple-system, BlinkMacSystemFont, sans-serif\n}\n"
                 "#transpert {\ncolor: white;\n}\n"
                 "</style>\n"
                 "<title>Звіт</title>\n</head>\n";

    return htmlHeader;
}



void MainWindow::on_report_triggered()
{
    if (isTableChoose)
    {
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop");
        if (!pathToSave.isEmpty())
        {
            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";


            for (int i = 0; i < tableModel->columnCount(); ++i)
            {
                textHTML += "   <th>" + tableModel->headerData(i, Qt::Horizontal ).toString() +"</th>\n";
            }

            textHTML += "</tr>\n";

            for (int i = 0; i < tableModel->rowCount(); ++i)
            {
                textHTML += "<tr>\n";

                for (int j = 0; j < tableModel->columnCount(); ++j)
                {
                    if (i % 2 not_eq 0)
                    {
                        textHTML += "   <td class='la'>" + tableModel->index(i,j).data().toString() + "</td>\n";
                    }
                    else
                    {
                        textHTML += "   <td>" + tableModel->index(i,j).data().toString() + "</td>\n";
                    }
                }
                textHTML += "</tr>\n";
            }
            textHTML+= "</tbody></table>";

            printDocumentToPDF(pathToSave + ".pdf", textHTML);

            QMessageBox::information(this,"","Звіт успішно збережено!");
        }
    }
    else
    {
        QMessageBox::information(this,"","Відкрийте сторінку тільки з таблицями!");
    }
}

