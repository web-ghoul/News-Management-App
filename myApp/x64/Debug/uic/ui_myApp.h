/********************************************************************************
** Form generated from reading UI file 'myApp.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYAPP_H
#define UI_MYAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myAppClass)
    {
        if (myAppClass->objectName().isEmpty())
            myAppClass->setObjectName("myAppClass");
        myAppClass->resize(600, 400);
        menuBar = new QMenuBar(myAppClass);
        menuBar->setObjectName("menuBar");
        myAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myAppClass);
        mainToolBar->setObjectName("mainToolBar");
        myAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(myAppClass);
        centralWidget->setObjectName("centralWidget");
        myAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(myAppClass);
        statusBar->setObjectName("statusBar");
        myAppClass->setStatusBar(statusBar);

        retranslateUi(myAppClass);

        QMetaObject::connectSlotsByName(myAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *myAppClass)
    {
        myAppClass->setWindowTitle(QCoreApplication::translate("myAppClass", "myApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myAppClass: public Ui_myAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYAPP_H
