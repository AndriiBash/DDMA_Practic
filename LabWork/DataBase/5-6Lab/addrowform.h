#ifndef ADDROWFORM_H
#define ADDROWFORM_H

#include <QWidget>

namespace Ui {
class AddRowForm;
}

class AddRowForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddRowForm(QWidget *parent = nullptr);
    ~AddRowForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddRowForm *ui;

signals:
    void signalSetData(QString lastName, QString name, QString fatherName, int year, QString postsqlAddRow);

};

#endif // ADDROWFORM_H
