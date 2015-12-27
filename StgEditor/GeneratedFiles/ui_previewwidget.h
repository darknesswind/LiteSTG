/********************************************************************************
** Form generated from reading UI file 'previewwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWWIDGET_H
#define UI_PREVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreviewWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_10;
    QDoubleSpinBox *sbZoom;
    QLabel *label_11;
    QLabel *lbSize;
    QLabel *lbPos;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *PreviewWidget)
    {
        if (PreviewWidget->objectName().isEmpty())
            PreviewWidget->setObjectName(QStringLiteral("PreviewWidget"));
        PreviewWidget->resize(258, 117);
        verticalLayout = new QVBoxLayout(PreviewWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(PreviewWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

        verticalLayout->addWidget(graphicsView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_10 = new QLabel(PreviewWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_2->addWidget(label_10);

        sbZoom = new QDoubleSpinBox(PreviewWidget);
        sbZoom->setObjectName(QStringLiteral("sbZoom"));
        sbZoom->setDecimals(5);
        sbZoom->setMaximum(1000);
        sbZoom->setValue(1);

        horizontalLayout_2->addWidget(sbZoom);

        label_11 = new QLabel(PreviewWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_2->addWidget(label_11);

        lbSize = new QLabel(PreviewWidget);
        lbSize->setObjectName(QStringLiteral("lbSize"));

        horizontalLayout_2->addWidget(lbSize);

        lbPos = new QLabel(PreviewWidget);
        lbPos->setObjectName(QStringLiteral("lbPos"));

        horizontalLayout_2->addWidget(lbPos);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(PreviewWidget);

        QMetaObject::connectSlotsByName(PreviewWidget);
    } // setupUi

    void retranslateUi(QWidget *PreviewWidget)
    {
        PreviewWidget->setWindowTitle(QApplication::translate("PreviewWidget", "PreviewWidget", 0));
        label_10->setText(QApplication::translate("PreviewWidget", "  Zoom:", 0));
        label_11->setText(QApplication::translate("PreviewWidget", "Size:", 0));
        lbSize->setText(QApplication::translate("PreviewWidget", "0x0", 0));
        lbPos->setText(QApplication::translate("PreviewWidget", "(0,0)", 0));
    } // retranslateUi

};

namespace Ui {
    class PreviewWidget: public Ui_PreviewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWWIDGET_H
