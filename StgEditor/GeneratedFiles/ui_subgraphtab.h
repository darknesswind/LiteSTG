/********************************************************************************
** Form generated from reading UI file 'subgraphtab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBGRAPHTAB_H
#define UI_SUBGRAPHTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubGraphTab
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *edName;
    QLabel *label_2;
    QComboBox *cbTexture;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *sbNumY;
    QSpinBox *sbNumX;
    QLabel *label_8;
    QSpinBox *sbSizeX;
    QSpinBox *sbSizeY;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_3;
    QSpinBox *sbSrcX;
    QSpinBox *sbSrcY;
    QLabel *label_9;
    QSpinBox *sbAllNum;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCopy;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QLabel *lbSize;
    QLabel *label_10;
    QDoubleSpinBox *sbZoom;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *SubGraphTab)
    {
        if (SubGraphTab->objectName().isEmpty())
            SubGraphTab->setObjectName(QStringLiteral("SubGraphTab"));
        SubGraphTab->resize(791, 533);
        horizontalLayout_3 = new QHBoxLayout(SubGraphTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(SubGraphTab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
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

        verticalLayout->addWidget(tableWidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SubGraphTab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        edName = new QLineEdit(SubGraphTab);
        edName->setObjectName(QStringLiteral("edName"));

        gridLayout->addWidget(edName, 0, 1, 1, 1);

        label_2 = new QLabel(SubGraphTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        cbTexture = new QComboBox(SubGraphTab);
        cbTexture->setObjectName(QStringLiteral("cbTexture"));

        gridLayout->addWidget(cbTexture, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(SubGraphTab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 2, 1, 1);

        label_4 = new QLabel(SubGraphTab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        sbNumY = new QSpinBox(SubGraphTab);
        sbNumY->setObjectName(QStringLiteral("sbNumY"));
        sbNumY->setMaximum(999999999);

        gridLayout_2->addWidget(sbNumY, 2, 3, 1, 1);

        sbNumX = new QSpinBox(SubGraphTab);
        sbNumX->setObjectName(QStringLiteral("sbNumX"));
        sbNumX->setMaximum(999999999);

        gridLayout_2->addWidget(sbNumX, 1, 3, 1, 1);

        label_8 = new QLabel(SubGraphTab);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 2, 4, 1, 1);

        sbSizeX = new QSpinBox(SubGraphTab);
        sbSizeX->setObjectName(QStringLiteral("sbSizeX"));
        sbSizeX->setMaximum(999999999);

        gridLayout_2->addWidget(sbSizeX, 1, 5, 1, 1);

        sbSizeY = new QSpinBox(SubGraphTab);
        sbSizeY->setObjectName(QStringLiteral("sbSizeY"));
        sbSizeY->setMaximum(999999999);

        gridLayout_2->addWidget(sbSizeY, 2, 5, 1, 1);

        label_6 = new QLabel(SubGraphTab);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 2, 1, 1);

        label_7 = new QLabel(SubGraphTab);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 4, 1, 1);

        label_3 = new QLabel(SubGraphTab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        sbSrcX = new QSpinBox(SubGraphTab);
        sbSrcX->setObjectName(QStringLiteral("sbSrcX"));
        sbSrcX->setMaximum(999999999);

        gridLayout_2->addWidget(sbSrcX, 1, 1, 1, 1);

        sbSrcY = new QSpinBox(SubGraphTab);
        sbSrcY->setObjectName(QStringLiteral("sbSrcY"));
        sbSrcY->setMaximum(999999999);

        gridLayout_2->addWidget(sbSrcY, 2, 1, 1, 1);

        label_9 = new QLabel(SubGraphTab);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 0, 2, 1, 1);

        sbAllNum = new QSpinBox(SubGraphTab);
        sbAllNum->setObjectName(QStringLiteral("sbAllNum"));
        sbAllNum->setMaximum(999999999);

        gridLayout_2->addWidget(sbAllNum, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCopy = new QPushButton(SubGraphTab);
        btnCopy->setObjectName(QStringLiteral("btnCopy"));

        horizontalLayout->addWidget(btnCopy);

        btnAdd = new QPushButton(SubGraphTab);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        horizontalLayout->addWidget(btnAdd);

        btnRemove = new QPushButton(SubGraphTab);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));

        horizontalLayout->addWidget(btnRemove);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphicsView = new QGraphicsView(SubGraphTab);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

        verticalLayout_2->addWidget(graphicsView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_11 = new QLabel(SubGraphTab);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_2->addWidget(label_11);

        lbSize = new QLabel(SubGraphTab);
        lbSize->setObjectName(QStringLiteral("lbSize"));

        horizontalLayout_2->addWidget(lbSize);

        label_10 = new QLabel(SubGraphTab);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_2->addWidget(label_10);

        sbZoom = new QDoubleSpinBox(SubGraphTab);
        sbZoom->setObjectName(QStringLiteral("sbZoom"));
        sbZoom->setDecimals(5);
        sbZoom->setMaximum(1000);
        sbZoom->setValue(1);

        horizontalLayout_2->addWidget(sbZoom);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(edName);
        label_2->setBuddy(cbTexture);
#endif // QT_NO_SHORTCUT

        retranslateUi(SubGraphTab);

        QMetaObject::connectSlotsByName(SubGraphTab);
    } // setupUi

    void retranslateUi(QWidget *SubGraphTab)
    {
        SubGraphTab->setWindowTitle(QApplication::translate("SubGraphTab", "SubGraphTab", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SubGraphTab", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SubGraphTab", "Texture", 0));
        label->setText(QApplication::translate("SubGraphTab", "&Name:", 0));
        label_2->setText(QApplication::translate("SubGraphTab", "&Texture:", 0));
        label_5->setText(QApplication::translate("SubGraphTab", "NumX", 0));
        label_4->setText(QApplication::translate("SubGraphTab", "SrcY", 0));
        label_8->setText(QApplication::translate("SubGraphTab", "SizeY", 0));
        label_6->setText(QApplication::translate("SubGraphTab", "NumY", 0));
        label_7->setText(QApplication::translate("SubGraphTab", "SizeX", 0));
        label_3->setText(QApplication::translate("SubGraphTab", "SrcX", 0));
        label_9->setText(QApplication::translate("SubGraphTab", "AllNum", 0));
        btnCopy->setText(QApplication::translate("SubGraphTab", "Copy", 0));
        btnAdd->setText(QApplication::translate("SubGraphTab", "Add", 0));
        btnRemove->setText(QApplication::translate("SubGraphTab", "Remove", 0));
        label_11->setText(QApplication::translate("SubGraphTab", "Size:", 0));
        lbSize->setText(QApplication::translate("SubGraphTab", "0x0", 0));
        label_10->setText(QApplication::translate("SubGraphTab", "  Zoom:", 0));
    } // retranslateUi

};

namespace Ui {
    class SubGraphTab: public Ui_SubGraphTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBGRAPHTAB_H
