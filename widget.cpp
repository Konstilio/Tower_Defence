#include "widget.h"
#include "ui_widget.h"

#include <QGridLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QGridLayout *Layout = new QGridLayout();
    mp_View = new GameView();

    Layout->addWidget(mp_View);
    setLayout(Layout);
}

Widget::~Widget()
{
    delete ui;
}
