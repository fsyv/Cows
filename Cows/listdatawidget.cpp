#include "listdatawidget.h"
#include "ui_listdatawidget.h"

ListDataWidget::ListDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListDataWidget)
{
    ui->setupUi(this);
}

ListDataWidget::~ListDataWidget()
{
    delete ui;
}
