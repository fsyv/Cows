#include "stdafx.h"

#include "listdatawidget.h"
#include "ui_listdatawidget.h"

#include "sqlexecute.h"

ListDataWidget::ListDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListDataWidget)
{
    ui->setupUi(this);

	loadData();
}

ListDataWidget::~ListDataWidget()
{
    delete ui;
}

void ListDataWidget::loadData()
{
	ui->listWidget->addItems(SQLExecute::getAllTableName());
}