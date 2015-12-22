/********************************************************************************
** Form generated from reading UI file 'texturetab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTURETAB_H
#define UI_TEXTURETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureTab
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TextureTab)
    {
        if (TextureTab->objectName().isEmpty())
            TextureTab->setObjectName(QStringLiteral("TextureTab"));
        TextureTab->resize(400, 300);
        gridLayout = new QGridLayout(TextureTab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableWidget = new QTableWidget(TextureTab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMouseTracking(true);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(25);

        horizontalLayout->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnAdd = new QPushButton(TextureTab);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        verticalLayout->addWidget(btnAdd);

        btnRemove = new QPushButton(TextureTab);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));

        verticalLayout->addWidget(btnRemove);

        verticalSpacer = new QSpacerItem(20, 138, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(TextureTab);

        QMetaObject::connectSlotsByName(TextureTab);
    } // setupUi

    void retranslateUi(QWidget *TextureTab)
    {
        TextureTab->setWindowTitle(QApplication::translate("TextureTab", "Form", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TextureTab", "Source", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TextureTab", "Name", 0));
        btnAdd->setText(QApplication::translate("TextureTab", "Add", 0));
        btnRemove->setText(QApplication::translate("TextureTab", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class TextureTab: public Ui_TextureTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTURETAB_H
