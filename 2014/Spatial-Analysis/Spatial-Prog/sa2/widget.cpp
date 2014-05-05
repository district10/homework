#include "widget.h"
#include "ui_widget.h"

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
