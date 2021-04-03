/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonSend;
    QLineEdit *lineEditSend;
    QProgressBar *progressBarRpm;
    QGroupBox *Polaczenie;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonLink;
    QPushButton *pushButtonClose;
    QComboBox *comboBoxDevices;
    QTextEdit *textEditLogi;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 287);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButtonSend = new QPushButton(centralwidget);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(180, 210, 80, 21));
        lineEditSend = new QLineEdit(centralwidget);
        lineEditSend->setObjectName(QString::fromUtf8("lineEditSend"));
        lineEditSend->setGeometry(QRect(10, 210, 151, 21));
        progressBarRpm = new QProgressBar(centralwidget);
        progressBarRpm->setObjectName(QString::fromUtf8("progressBarRpm"));
        progressBarRpm->setGeometry(QRect(280, 100, 101, 23));
        progressBarRpm->setValue(24);
        Polaczenie = new QGroupBox(centralwidget);
        Polaczenie->setObjectName(QString::fromUtf8("Polaczenie"));
        Polaczenie->setGeometry(QRect(10, 10, 381, 51));
        pushButtonSearch = new QPushButton(Polaczenie);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));
        pushButtonSearch->setGeometry(QRect(10, 23, 51, 23));
        pushButtonLink = new QPushButton(Polaczenie);
        pushButtonLink->setObjectName(QString::fromUtf8("pushButtonLink"));
        pushButtonLink->setGeometry(QRect(250, 22, 61, 23));
        pushButtonClose = new QPushButton(Polaczenie);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(320, 22, 51, 23));
        comboBoxDevices = new QComboBox(Polaczenie);
        comboBoxDevices->setObjectName(QString::fromUtf8("comboBoxDevices"));
        comboBoxDevices->setGeometry(QRect(70, 23, 171, 22));
        textEditLogi = new QTextEdit(centralwidget);
        textEditLogi->setObjectName(QString::fromUtf8("textEditLogi"));
        textEditLogi->setGeometry(QRect(10, 70, 251, 131));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("MainWindow", "Wy\305\233lij", nullptr));
        Polaczenie->setTitle(QCoreApplication::translate("MainWindow", "Po\305\202\304\205czenie", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("MainWindow", "Szukaj", nullptr));
        pushButtonLink->setText(QCoreApplication::translate("MainWindow", "Po\305\202\304\205cz", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MainWindow", "Roz\305\202\304\205cz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
