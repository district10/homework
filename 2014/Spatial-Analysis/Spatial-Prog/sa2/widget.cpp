#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->rbpoint->setChecked(true);
    ui->buffsize->setValue(20);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        ui->label_2->setText("aaaaaaa");
        break;
    case Qt::Key_Down:
        ui->label_2->setText("bbbbbbb");
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        ui->label_2->setText("ccccccc");
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int r = ui->buffsize->value();

    ui->label_2->setText(QString::number(r*r));

}
