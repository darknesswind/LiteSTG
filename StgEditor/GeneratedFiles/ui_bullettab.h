/********************************************************************************
** Form generated from reading UI file 'bullettab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BULLETTAB_H
#define UI_BULLETTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "previewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_BulletTab
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    PreviewWidget *preview;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCopy;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout;
    QLabel *label_8;
    QLineEdit *edName;
    QLabel *label_6;
    QComboBox *cbType;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *cbCollide;
    QLabel *label_2;
    QDoubleSpinBox *sbCenterX;
    QLabel *label_3;
    QDoubleSpinBox *sbCenterY;
    QLabel *label_4;
    QDoubleSpinBox *sbRadianX;
    QLabel *label_5;
    QDoubleSpinBox *sbRadianY;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *rbSubGraph;
    QComboBox *cbSubGraph;
    QRadioButton *rbAnime;
    QComboBox *comboBox_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *BulletTab)
    {
        if (BulletTab->objectName().isEmpty())
            BulletTab->setObjectName(QStringLiteral("BulletTab"));
        BulletTab->resize(564, 536);
        horizontalLayout_2 = new QHBoxLayout(BulletTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        preview = new PreviewWidget(BulletTab);
        preview->setObjectName(QStringLiteral("preview"));
        preview->setMinimumSize(QSize(100, 100));

        verticalLayout_3->addWidget(preview);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tableWidget = new QTableWidget(BulletTab);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        tableWidget->verticalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_2->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCopy = new QPushButton(BulletTab);
        btnCopy->setObjectName(QStringLiteral("btnCopy"));

        horizontalLayout->addWidget(btnCopy);

        btnAdd = new QPushButton(BulletTab);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        horizontalLayout->addWidget(btnAdd);

        btnRemove = new QPushButton(BulletTab);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));

        horizontalLayout->addWidget(btnRemove);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 5);

        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_3 = new QGroupBox(BulletTab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout = new QFormLayout(groupBox_3);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        edName = new QLineEdit(groupBox_3);
        edName->setObjectName(QStringLiteral("edName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, edName);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        cbType = new QComboBox(groupBox_3);
        cbType->setObjectName(QStringLiteral("cbType"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cbType);


        verticalLayout->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(BulletTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        cbCollide = new QComboBox(groupBox_2);
        cbCollide->setObjectName(QStringLiteral("cbCollide"));

        gridLayout_2->addWidget(cbCollide, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        sbCenterX = new QDoubleSpinBox(groupBox_2);
        sbCenterX->setObjectName(QStringLiteral("sbCenterX"));
        sbCenterX->setDecimals(4);
        sbCenterX->setMinimum(-100);
        sbCenterX->setMaximum(100);

        gridLayout_2->addWidget(sbCenterX, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        sbCenterY = new QDoubleSpinBox(groupBox_2);
        sbCenterY->setObjectName(QStringLiteral("sbCenterY"));
        sbCenterY->setDecimals(4);
        sbCenterY->setMinimum(-100);
        sbCenterY->setMaximum(100);

        gridLayout_2->addWidget(sbCenterY, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        sbRadianX = new QDoubleSpinBox(groupBox_2);
        sbRadianX->setObjectName(QStringLiteral("sbRadianX"));
        sbRadianX->setDecimals(4);
        sbRadianX->setMaximum(100);

        gridLayout_2->addWidget(sbRadianX, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        sbRadianY = new QDoubleSpinBox(groupBox_2);
        sbRadianY->setObjectName(QStringLiteral("sbRadianY"));
        sbRadianY->setDecimals(4);
        sbRadianY->setMaximum(100);

        gridLayout_2->addWidget(sbRadianY, 4, 1, 1, 1);

        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnMinimumWidth(1, 1);

        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(BulletTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        rbSubGraph = new QRadioButton(groupBox);
        rbSubGraph->setObjectName(QStringLiteral("rbSubGraph"));
        rbSubGraph->setChecked(true);

        gridLayout->addWidget(rbSubGraph, 0, 0, 1, 1);

        cbSubGraph = new QComboBox(groupBox);
        cbSubGraph->setObjectName(QStringLiteral("cbSubGraph"));

        gridLayout->addWidget(cbSubGraph, 0, 1, 1, 1);

        rbAnime = new QRadioButton(groupBox);
        rbAnime->setObjectName(QStringLiteral("rbAnime"));

        gridLayout->addWidget(rbAnime, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setEnabled(false);

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label_8->setBuddy(edName);
        label_6->setBuddy(cbType);
        label->setBuddy(cbCollide);
        label_2->setBuddy(sbCenterX);
        label_3->setBuddy(sbCenterY);
        label_4->setBuddy(sbRadianX);
        label_5->setBuddy(sbRadianY);
#endif // QT_NO_SHORTCUT

        retranslateUi(BulletTab);
        QObject::connect(rbSubGraph, SIGNAL(toggled(bool)), cbSubGraph, SLOT(setEnabled(bool)));
        QObject::connect(rbAnime, SIGNAL(toggled(bool)), comboBox_2, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(BulletTab);
    } // setupUi

    void retranslateUi(QWidget *BulletTab)
    {
        BulletTab->setWindowTitle(QApplication::translate("BulletTab", "BulletTab", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BulletTab", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BulletTab", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BulletTab", "CollideType", 0));
        btnCopy->setText(QApplication::translate("BulletTab", "Copy", 0));
        btnAdd->setText(QApplication::translate("BulletTab", "Add", 0));
        btnRemove->setText(QApplication::translate("BulletTab", "Remove", 0));
        groupBox_3->setTitle(QApplication::translate("BulletTab", "Base", 0));
        label_8->setText(QApplication::translate("BulletTab", "Name:", 0));
        label_6->setText(QApplication::translate("BulletTab", "Type:", 0));
        cbType->clear();
        cbType->insertItems(0, QStringList()
         << QApplication::translate("BulletTab", "General", 0)
         << QApplication::translate("BulletTab", "Ray Laser", 0)
         << QApplication::translate("BulletTab", "Segment Laser", 0)
         << QApplication::translate("BulletTab", "Curve Laser", 0)
        );
        groupBox_2->setTitle(QApplication::translate("BulletTab", "Collide", 0));
        label->setText(QApplication::translate("BulletTab", "CollideType:", 0));
        cbCollide->clear();
        cbCollide->insertItems(0, QStringList()
         << QApplication::translate("BulletTab", "Circle", 0)
         << QApplication::translate("BulletTab", "Rectangle", 0)
        );
        label_2->setText(QApplication::translate("BulletTab", "Center X:", 0));
        label_3->setText(QApplication::translate("BulletTab", "Center Y:", 0));
        label_4->setText(QApplication::translate("BulletTab", "Radian X:", 0));
        label_5->setText(QApplication::translate("BulletTab", "Radian Y:", 0));
        groupBox->setTitle(QApplication::translate("BulletTab", "Visual", 0));
        rbSubGraph->setText(QApplication::translate("BulletTab", "GraphGroup:", 0));
        rbAnime->setText(QApplication::translate("BulletTab", "AnimeGroup:", 0));
    } // retranslateUi

};

namespace Ui {
    class BulletTab: public Ui_BulletTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BULLETTAB_H
