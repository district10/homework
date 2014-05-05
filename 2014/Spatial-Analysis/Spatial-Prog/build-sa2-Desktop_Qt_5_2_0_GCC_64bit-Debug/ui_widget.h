/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbpoint;
    QRadioButton *rbline;
    QRadioButton *rbpolygon;
    QDial *buffsize;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QWidget *canvas;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(565, 334);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rbpoint = new QRadioButton(Widget);
        rbpoint->setObjectName(QStringLiteral("rbpoint"));

        verticalLayout_2->addWidget(rbpoint);

        rbline = new QRadioButton(Widget);
        rbline->setObjectName(QStringLiteral("rbline"));

        verticalLayout_2->addWidget(rbline);

        rbpolygon = new QRadioButton(Widget);
        rbpolygon->setObjectName(QStringLiteral("rbpolygon"));

        verticalLayout_2->addWidget(rbpolygon);


        verticalLayout->addLayout(verticalLayout_2);

        buffsize = new QDial(Widget);
        buffsize->setObjectName(QStringLiteral("buffsize"));
        buffsize->setCursor(QCursor(Qt::PointingHandCursor));
        buffsize->setMinimum(0);
        buffsize->setMaximum(40);
        buffsize->setSingleStep(5);

        verticalLayout->addWidget(buffsize);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        canvas = new QWidget(Widget);
        canvas->setObjectName(QStringLiteral("canvas"));
        canvas->setMinimumSize(QSize(361, 0));
        canvas->setCursor(QCursor(Qt::CrossCursor));
        canvas->setMouseTracking(true);
        canvas->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(canvas);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(Widget);
        QObject::connect(buffsize, SIGNAL(valueChanged(int)), label_2, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\347\274\223\345\206\262\345\214\272DEMO--QT-Widget", 0));
        rbpoint->setText(QApplication::translate("Widget", "Point", 0));
        rbline->setText(QApplication::translate("Widget", "Line", 0));
        rbpolygon->setText(QApplication::translate("Widget", "Polygon", 0));
        label->setText(QApplication::translate("Widget", "BuffSize:", 0));
        label_2->setText(QApplication::translate("Widget", "0", 0));
#ifndef QT_NO_TOOLTIP
        canvas->setToolTip(QApplication::translate("Widget", "<html><head/><body><p>\345\267\246\351\224\256\345\212\240\347\202\271\357\274\214\345\217\263\351\224\256\345\256\214\346\210\220</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H