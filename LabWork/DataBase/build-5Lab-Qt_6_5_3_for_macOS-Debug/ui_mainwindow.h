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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *AddRowAction;
    QAction *DeleteRowAction;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        AddRowAction = new QAction(MainWindow);
        AddRowAction->setObjectName("AddRowAction");
        DeleteRowAction = new QAction(MainWindow);
        DeleteRowAction->setObjectName("DeleteRowAction");
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

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AddRowAction->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\267\320\260\320\277\320\270\321\201", nullptr));
        DeleteRowAction->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \320\267\320\260\320\277\320\270\321\201", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
