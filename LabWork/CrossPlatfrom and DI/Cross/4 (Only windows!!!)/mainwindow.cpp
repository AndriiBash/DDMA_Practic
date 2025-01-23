#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QAxObject>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileName = "";
}

MainWindow::~MainWindow()
{
    m_word->dynamicCall("Quit()"); // Закриваємо Word
    delete words;
    delete newDocument;
    delete documents;
    delete m_word;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Відкриваємо діалог вибору файлу
    QString filter = "Word файли (*.docx *.doc);;Усі файли (*.*)";
    fileName = QFileDialog::getOpenFileName(this, "Виберіть Word файл", QDir::homePath(), filter);

    if (fileName.isEmpty()) {
        return;
    }

    QFileInfo fileinfo(fileName);
    m_word = new QAxObject("Word.Application", 0); // Створюємо об'єкт для роботи з Word
    documents = m_word->querySubObject("Documents"); // Знаходимо колекцію документів
    newDocument = documents->querySubObject("Open(const QString&)", fileName); // Відкриваємо документ
    m_word->setProperty("Visible", true); // Робимо Word видимим

    words = newDocument->querySubObject("Words"); // Знаходимо колекцію слів в документі

    int countWordsStartingWithA = 0;
    int wordCount = words->dynamicCall("Count()").toInt(); // Загальна кількість слів

    for (int i = 1; i <= wordCount; i++) {
        QString word = words->querySubObject("Item(int)", i)->dynamicCall("Text()").toString().trimmed();
        if (word.startsWith("a", Qt::CaseInsensitive)) {
            countWordsStartingWithA++;
        }
    }

    // Створюємо результат
    QString result = QString("Кількість слів, які починаються з літери 'a': %1").arg(countWordsStartingWithA);


    QString textResult;
    int countWord = words->dynamicCall("Count()").toInt(); // зчитуємо з коллекції їх кількість
    for (int a = 1; a <= countWord; a++) { // перебираємо всі слова
        textResult.append(words->querySubObject("Item(int)", a)->dynamicCall("Text()").toString());
    }

    // Вставляємо результат у PlainTextEdit
    ui->plainTextEdit->setPlainText(textResult + result); // Встановлюємо текст в PlainTextEdit
}
