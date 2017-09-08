/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_rgb;
    QWidget *tab_2;
    QLabel *label_depth;
    QWidget *tab_3;
    QLabel *label_ir;
    QPushButton *captureBtn;
    QPushButton *openCaptureBtn;
    QCheckBox *checkBox;
    QCheckBox *checkBox_corners;
    QSlider *hSlider_ir;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(893, 628);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 691, 541));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_rgb = new QLabel(tab);
        label_rgb->setObjectName(QStringLiteral("label_rgb"));
        label_rgb->setGeometry(QRect(10, 20, 640, 480));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_depth = new QLabel(tab_2);
        label_depth->setObjectName(QStringLiteral("label_depth"));
        label_depth->setGeometry(QRect(10, 20, 640, 480));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_ir = new QLabel(tab_3);
        label_ir->setObjectName(QStringLiteral("label_ir"));
        label_ir->setGeometry(QRect(10, 20, 640, 480));
        tabWidget->addTab(tab_3, QString());
        captureBtn = new QPushButton(centralWidget);
        captureBtn->setObjectName(QStringLiteral("captureBtn"));
        captureBtn->setGeometry(QRect(720, 170, 75, 23));
        openCaptureBtn = new QPushButton(centralWidget);
        openCaptureBtn->setObjectName(QStringLiteral("openCaptureBtn"));
        openCaptureBtn->setGeometry(QRect(720, 40, 131, 23));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(730, 90, 71, 16));
        checkBox_corners = new QCheckBox(centralWidget);
        checkBox_corners->setObjectName(QStringLiteral("checkBox_corners"));
        checkBox_corners->setGeometry(QRect(730, 130, 92, 23));
        hSlider_ir = new QSlider(centralWidget);
        hSlider_ir->setObjectName(QStringLiteral("hSlider_ir"));
        hSlider_ir->setGeometry(QRect(710, 220, 160, 16));
        hSlider_ir->setMaximum(120);
        hSlider_ir->setValue(50);
        hSlider_ir->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 893, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_rgb->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "rgb", Q_NULLPTR));
        label_depth->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "depth", Q_NULLPTR));
        label_ir->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "ir", Q_NULLPTR));
        captureBtn->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", Q_NULLPTR));
        openCaptureBtn->setText(QApplication::translate("MainWindow", "open Camera", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "ir", Q_NULLPTR));
        checkBox_corners->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\350\247\222\347\202\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
