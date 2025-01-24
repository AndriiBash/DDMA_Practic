#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileName = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openTable_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Відкрити файл", "C://");

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    // за допомогою QAxObject отримуємо покажчик на Excel(СOMObject)
    excel = new QAxObject("Excel.Application");
    workbooks = excel->querySubObject("Workbooks"); // робоча книга
    workbook = workbooks->querySubObject("Open(constQString&)",fileName);
    excel->dynamicCall("SetVisible(bool)",false); // видимість документу
    sheet = workbook->querySubObject("WorkSheets(int)",1);

    QAxObject* usedrange = sheet->querySubObject("UsedRange");
    QAxObject* rows = usedrange->querySubObject("Rows");
    QAxObject* columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    ui->tableWidget->setColumnCount(intColStart+intCols);
    ui->tableWidget->setRowCount(intRowStart+intRows);

    //зчитуємо дані знаючи кількість стовпців та строк в наш TableWidget
    for(int row = 0; row < intRows; row++)
    {
        for(int col=0; col < intCols; col++)
        {
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", row + 1, col + 1);
            QVariant value = cell->dynamicCall("Value()");
            QTableWidgetItem *item = new
            QTableWidgetItem(value.toString());
            ui->tableWidget->setItem(row,col,item);
        }
    }
}


void MainWindow::on_calculate_clicked()
{
    // Для рядка "Сума"
    QAxObject *cell1 = sheet->querySubObject("Cells(int,int)", 10, 1);
    QAxObject *cell_1 = sheet->querySubObject("Cells(int,int)", 10, 2);
    QAxObject *cell_2 = sheet->querySubObject("Cells(int,int)", 10, 3);

    cell1->setProperty("Value", "Сума");            // Вставляємо текст "Сума" у комірку A10
    cell_1->setProperty("Formula", "=SUM(B2:B9)"); // Формула для підрахунку суми стовпця B у комірці B10
    cell_2->setProperty("Formula", "=SUM(C2:C9)"); // Формула для підрахунку суми стовпця C у комірці C10

    // Для рядка "Середнє значення"
    QAxObject *cell2 = sheet->querySubObject("Cells(int,int)", 11, 1);
    QAxObject *cell_3 = sheet->querySubObject("Cells(int,int)", 11, 2);
    QAxObject *cell_4 = sheet->querySubObject("Cells(int,int)", 11, 3);

    cell2->setProperty("Value", "Середнє значення");    // Вставляємо текст "Середнє значення" у комірку A11
    cell_3->setProperty("Formula", "=AVERAGE(B2:B9)");  // Формула для підрахунку середнього значення стовпця B у комірці B11
    cell_4->setProperty("Formula", "=AVERAGE(C2:C9)");  // Формула для підрахунку середнього значення стовпця C у комірці C11

    delete cell2;
    delete cell_3;
    delete cell_4;
    delete cell_2;
    delete cell_1;
    delete cell1;
    sheet->clear();
    delete sheet;
    sheet = NULL;
    workbook->clear();
    delete workbook;
    workbook = NULL;
    workbooks->dynamicCall( "Close" );
    workbooks->clear();
    delete workbooks;
    workbooks = NULL;
    excel->dynamicCall( "Quit" );
    delete excel;
    excel = NULL;
}

