#include "stdafx.h"

#include "listdatawidget.h"
#include "ui_listdatawidget.h"

#include "tablewidget.h"

#include "sqlexecute.h"

ListDataWidget::ListDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListDataWidget)
{
    ui->setupUi(this);

	connect(ui->listWidget, &QListWidget::doubleClicked, this, &ListDataWidget::showData);

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

void ListDataWidget::showData(const QModelIndex &index)
{
	//hide();
	TableWidget tableWidget(
		SQLExecute::importData(
		ui->listWidget->item(index.row())->text()
		)
		);
	tableWidget.exec();
	//show();
}