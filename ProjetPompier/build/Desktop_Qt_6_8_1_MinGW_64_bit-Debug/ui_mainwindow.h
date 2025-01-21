/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_Valider;
    QPushButton *pushButton_Clear;
    QPushButton *pushButton_Multiplier;
    QTextBrowser *textBrowser_AffPrix;
    QTextBrowser *textBrowser_DerArticle;
    QTextBrowser *textBrowser_Carte;
    QListView *listView_Articles;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QTextBrowser *textBrowser_EAN;
    QPushButton *pushButton_Total;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_0;
    QPushButton *pushButton_virgule;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1546, 935);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton_1 = new QPushButton(centralwidget);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setGeometry(QRect(880, 500, 151, 91));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setUnderline(false);
        pushButton_1->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1040, 500, 151, 91));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(1200, 500, 151, 91));
        pushButton_3->setFont(font);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(880, 600, 151, 91));
        pushButton_4->setFont(font);
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1040, 600, 151, 91));
        pushButton_5->setFont(font);
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(1200, 600, 151, 91));
        pushButton_6->setFont(font);
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(880, 699, 151, 91));
        pushButton_7->setFont(font);
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1040, 699, 151, 91));
        pushButton_8->setFont(font);
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1200, 699, 151, 91));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        pushButton_9->setFont(font1);
        pushButton_Valider = new QPushButton(centralwidget);
        pushButton_Valider->setObjectName("pushButton_Valider");
        pushButton_Valider->setGeometry(QRect(1360, 699, 171, 191));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        pushButton_Valider->setFont(font2);
        pushButton_Clear = new QPushButton(centralwidget);
        pushButton_Clear->setObjectName("pushButton_Clear");
        pushButton_Clear->setGeometry(QRect(880, 799, 151, 91));
        pushButton_Clear->setFont(font);
        pushButton_Multiplier = new QPushButton(centralwidget);
        pushButton_Multiplier->setObjectName("pushButton_Multiplier");
        pushButton_Multiplier->setGeometry(QRect(1360, 400, 171, 91));
        pushButton_Multiplier->setFont(font);
        textBrowser_AffPrix = new QTextBrowser(centralwidget);
        textBrowser_AffPrix->setObjectName("textBrowser_AffPrix");
        textBrowser_AffPrix->setGeometry(QRect(590, 699, 251, 91));
        QFont font3;
        font3.setPointSize(35);
        font3.setBold(false);
        textBrowser_AffPrix->setFont(font3);
        textBrowser_DerArticle = new QTextBrowser(centralwidget);
        textBrowser_DerArticle->setObjectName("textBrowser_DerArticle");
        textBrowser_DerArticle->setGeometry(QRect(20, 699, 561, 91));
        textBrowser_Carte = new QTextBrowser(centralwidget);
        textBrowser_Carte->setObjectName("textBrowser_Carte");
        textBrowser_Carte->setGeometry(QRect(20, 800, 821, 91));
        listView_Articles = new QListView(centralwidget);
        listView_Articles->setObjectName("listView_Articles");
        listView_Articles->setGeometry(QRect(20, 10, 821, 681));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(1100, 190, 211, 171));
        pushButton_13->setFont(font);
        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(1320, 190, 211, 171));
        pushButton_14->setFont(font);
        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(880, 190, 211, 171));
        pushButton_15->setFont(font);
        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(880, 10, 211, 171));
        pushButton_16->setFont(font);
        textBrowser_EAN = new QTextBrowser(centralwidget);
        textBrowser_EAN->setObjectName("textBrowser_EAN");
        textBrowser_EAN->setGeometry(QRect(880, 400, 471, 91));
        QFont font4;
        font4.setPointSize(20);
        textBrowser_EAN->setFont(font4);
        pushButton_Total = new QPushButton(centralwidget);
        pushButton_Total->setObjectName("pushButton_Total");
        pushButton_Total->setGeometry(QRect(1360, 500, 171, 191));
        pushButton_Total->setFont(font2);
        pushButton_18 = new QPushButton(centralwidget);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(1100, 10, 211, 171));
        pushButton_18->setFont(font);
        pushButton_19 = new QPushButton(centralwidget);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(1320, 10, 211, 171));
        pushButton_19->setFont(font);
        pushButton_0 = new QPushButton(centralwidget);
        pushButton_0->setObjectName("pushButton_0");
        pushButton_0->setGeometry(QRect(1040, 800, 151, 91));
        pushButton_0->setFont(font);
        pushButton_virgule = new QPushButton(centralwidget);
        pushButton_virgule->setObjectName("pushButton_virgule");
        pushButton_virgule->setGeometry(QRect(1200, 800, 151, 91));
        pushButton_virgule->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1546, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_Valider->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("MainWindow", "CLEAR", nullptr));
        pushButton_Multiplier->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        textBrowser_AffPrix->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:35pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:700;\">124,72\342\202\254</span></p></body></html>", nullptr));
        textBrowser_DerArticle->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">CocaCola Zero			1,99\342\202\254</span></p></body></html>", nullptr));
        textBrowser_Carte->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700;\">Carte de Martigan : 100,50\342\202\254</span></p></body></html>", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "AnnLigne", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "DerLigne", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "AnnLigne", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Remise", nullptr));
        textBrowser_EAN->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton_Total->setText(QCoreApplication::translate("MainWindow", "Total", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "Remise", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "Remise", nullptr));
        pushButton_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_virgule->setText(QCoreApplication::translate("MainWindow", ",", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
