/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *AddNew;
    QAction *DeleteRow;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableView;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTableView *tableView_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView_3;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_5;
    QTableView *tableView_4;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_6;
    QTableView *tableView_5;
    QWidget *tab_6;
    QHBoxLayout *horizontalLayout_7;
    QTableView *tableView_6;
    QWidget *tab_7;
    QHBoxLayout *horizontalLayout_8;
    QTableView *tableView_7;
    QWidget *tab_8;
    QHBoxLayout *horizontalLayout_9;
    QTableView *tableView_8;
    QWidget *tab_9;
    QHBoxLayout *horizontalLayout_10;
    QTableView *tableView_9;
    QWidget *tab_10;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_11;
    QTableView *tableView_10;
    QTableView *tableView_11;
    QWidget *tab_11;
    QVBoxLayout *verticalLayout_2;
    QTableView *sqlTableView;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *tab_12;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableView_12;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *tab_13;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        AddNew = new QAction(MainWindow);
        AddNew->setObjectName("AddNew");
        DeleteRow = new QAction(MainWindow);
        DeleteRow->setObjectName("DeleteRow");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        tableView = new QTableView(tab);
        tableView->setObjectName("tableView");
        tableView->setSortingEnabled(true);

        horizontalLayout_2->addWidget(tableView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tableView_2 = new QTableView(tab_2);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setSortingEnabled(true);

        horizontalLayout_3->addWidget(tableView_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        horizontalLayout_4 = new QHBoxLayout(tab_3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        tableView_3 = new QTableView(tab_3);
        tableView_3->setObjectName("tableView_3");
        tableView_3->setSortingEnabled(true);

        horizontalLayout_4->addWidget(tableView_3);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        horizontalLayout_5 = new QHBoxLayout(tab_4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        tableView_4 = new QTableView(tab_4);
        tableView_4->setObjectName("tableView_4");
        tableView_4->setSortingEnabled(true);

        horizontalLayout_5->addWidget(tableView_4);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        horizontalLayout_6 = new QHBoxLayout(tab_5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        tableView_5 = new QTableView(tab_5);
        tableView_5->setObjectName("tableView_5");
        tableView_5->setSortingEnabled(true);

        horizontalLayout_6->addWidget(tableView_5);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        horizontalLayout_7 = new QHBoxLayout(tab_6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        tableView_6 = new QTableView(tab_6);
        tableView_6->setObjectName("tableView_6");
        tableView_6->setSortingEnabled(true);

        horizontalLayout_7->addWidget(tableView_6);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        horizontalLayout_8 = new QHBoxLayout(tab_7);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        tableView_7 = new QTableView(tab_7);
        tableView_7->setObjectName("tableView_7");
        tableView_7->setSortingEnabled(true);

        horizontalLayout_8->addWidget(tableView_7);

        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        horizontalLayout_9 = new QHBoxLayout(tab_8);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        tableView_8 = new QTableView(tab_8);
        tableView_8->setObjectName("tableView_8");
        tableView_8->setSortingEnabled(true);

        horizontalLayout_9->addWidget(tableView_8);

        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        horizontalLayout_10 = new QHBoxLayout(tab_9);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        tableView_9 = new QTableView(tab_9);
        tableView_9->setObjectName("tableView_9");
        tableView_9->setSortingEnabled(true);

        horizontalLayout_10->addWidget(tableView_9);

        tabWidget->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        verticalLayout = new QVBoxLayout(tab_10);
        verticalLayout->setObjectName("verticalLayout");
        frame_2 = new QFrame(tab_10);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("QFrame#frame_2\n"
"{\n"
"	border: 0px;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_12 = new QHBoxLayout(frame_2);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_2);
        label->setObjectName("label");

        horizontalLayout_12->addWidget(label);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");

        horizontalLayout_12->addWidget(label_2);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(tab_10);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("QFrame#frame\n"
"{\n"
"	border: 0px;\n"
"}\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(frame);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        tableView_10 = new QTableView(frame);
        tableView_10->setObjectName("tableView_10");

        horizontalLayout_11->addWidget(tableView_10);

        tableView_11 = new QTableView(frame);
        tableView_11->setObjectName("tableView_11");

        horizontalLayout_11->addWidget(tableView_11);


        verticalLayout->addWidget(frame);

        tabWidget->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName("tab_11");
        verticalLayout_2 = new QVBoxLayout(tab_11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        sqlTableView = new QTableView(tab_11);
        sqlTableView->setObjectName("sqlTableView");
        sqlTableView->setSortingEnabled(true);

        verticalLayout_2->addWidget(sqlTableView);

        frame_3 = new QFrame(tab_11);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border: 0px;\n"
"\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frame_3);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_13->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_13->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_13->addWidget(pushButton_3);


        verticalLayout_2->addWidget(frame_3);

        tabWidget->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName("tab_12");
        verticalLayout_4 = new QVBoxLayout(tab_12);
        verticalLayout_4->setObjectName("verticalLayout_4");
        tableView_12 = new QTableView(tab_12);
        tableView_12->setObjectName("tableView_12");

        verticalLayout_4->addWidget(tableView_12);

        frame_4 = new QFrame(tab_12);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border: 0px;\n"
"\n"
"}"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(frame_4);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        pushButton_4 = new QPushButton(frame_4);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_14->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(frame_4);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout_14->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(frame_4);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout_14->addWidget(pushButton_6);


        verticalLayout_4->addWidget(frame_4);

        tabWidget->addTab(tab_12, QString());
        tab_13 = new QWidget();
        tab_13->setObjectName("tab_13");
        verticalLayout_3 = new QVBoxLayout(tab_13);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tableWidget = new QTableWidget(tab_13);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_3->addWidget(tableWidget);

        textEdit = new QTextEdit(tab_13);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);

        verticalLayout_3->addWidget(textEdit);

        frame_5 = new QFrame(tab_13);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"border: 0px;\n"
"}"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_15 = new QHBoxLayout(frame_5);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");

        horizontalLayout_15->addWidget(label_3);

        lineEdit = new QLineEdit(frame_5);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_15->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(frame_5);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_15->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(frame_5);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_15->addWidget(lineEdit_3);


        verticalLayout_3->addWidget(frame_5);

        frame_6 = new QFrame(tab_13);
        frame_6->setObjectName("frame_6");
        frame_6->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
" border: 0px;\n"
"}"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_16 = new QHBoxLayout(frame_6);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        pushButton_7 = new QPushButton(frame_6);
        pushButton_7->setObjectName("pushButton_7");

        horizontalLayout_16->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(frame_6);
        pushButton_8->setObjectName("pushButton_8");

        horizontalLayout_16->addWidget(pushButton_8);


        verticalLayout_3->addWidget(frame_6);

        tabWidget->addTab(tab_13, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName("toolBar_2");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        toolBar_2->addAction(AddNew);
        toolBar_2->addAction(DeleteRow);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(12);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AddNew->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\267\320\260\320\277\320\270\321\201", nullptr));
        DeleteRow->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \320\267\320\260\320\277\320\270\321\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\227\320\260\320\262\320\264\320\260\320\275\320\275\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\222\320\270\320\272\320\276\320\275\321\203\321\224 \320\267\320\260\320\262\320\264\320\260\320\275\320\275\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\236\320\261\320\273\320\260\320\264\320\275\320\260\320\275\320\275\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\320\222\320\270\320\272\320\276\321\200\320\270\321\201\321\202\320\276\320\262\321\203\321\224", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\321\206\321\226\320\262\320\275\320\270\320\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\320\206\320\275\321\201\321\202\321\203\320\274\320\265\320\275\321\202\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\320\237\321\226\320\264\320\262\320\270\321\211\321\203\321\224 \320\272\320\262\320\260\320\273\321\226\321\204\321\226\320\272\320\260\321\206\321\226\321\216", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QCoreApplication::translate("MainWindow", "\320\232\320\262\320\260\320\273\321\226\321\204\321\226\320\272\320\260\321\206\321\226\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\275\320\260\320\262\321\207\320\260\320\275\320\275\321\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">\320\237\321\200\320\260\321\206\321\226\320\262\320\275\320\270\320\272\320\270</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">\320\222\320\270\320\272\320\276\321\200\320\270\321\201\321\202\320\276\320\262\321\203\321\224 </span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_10), QCoreApplication::translate("MainWindow", "\320\227\320\262'\321\217\320\267\320\275\321\226\321\201\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\321\210\320\270\320\271 \320\267\320\260\320\277\320\270\321\202", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\224\321\200\321\203\320\263\320\270\320\271 \320\267\320\260\320\277\320\270\321\202", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\265\321\202\321\226\320\271 \320\267\320\260\320\277\320\270\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_11), QCoreApplication::translate("MainWindow", "SQL \320\267\320\260\320\277\320\270\321\202\320\270", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\262\320\260\320\275\321\202\320\260\320\266\320\270\321\202\320\270 \321\202\320\260\320\261\320\273\320\270\321\206\321\216", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\210\321\203\320\272 \320\277\320\276\321\201\320\260\320\264\320\270 \320\277\321\200\320\260\321\206\321\226\320\262\320\275\320\270\320\272\320\260 \320\267\320\260 ID", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\321\203\320\262\320\260\321\202\320\270 \320\267\320\260 \321\200\321\226\320\272\320\276\320\274 \320\275\320\260\321\200\320\276\320\264\320\266\320\265\320\275\320\275\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_12), QCoreApplication::translate("MainWindow", "SqlQueryTable", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">\320\224\320\273\321\217 Where</span></p></body></html>", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260 \321\226\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\260", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \321\226\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\260", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201 \321\226\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\260", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\321\203\320\262\320\260\321\202\320\270", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\320\236\320\275\320\276\320\262\320\270\321\202\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_13), QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
