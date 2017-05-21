#include "stdafx.h"

#include "listdatawidget.h"
#include "ui_listdatawidget.h"

#include "sqlexecute.h"

ListDataWidget::ListDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListDataWidget)
{
    ui->setupUi(this);

	connect(ui->listWidget, &QListWidget::doubleClicked, this, &ListDataWidget::showData);
}

ListDataWidget::~ListDataWidget()
{
    delete ui;
}

void ListDataWidget::showEvent(QShowEvent *e)
{
	clearData();
	loadData();
}

void ListDataWidget::loadData()
{
	ui->listWidget->addItems(SQLExecute::getAllTableName());
}

void ListDataWidget::clearData()
{
	ui->listWidget->clear();
}

void ListDataWidget::showData(const QModelIndex &index)
{
	//hide();
	/*TableWidget tableWidget(
		SQLExecute::importData(
		ui->listWidget->item(index.row())->text()
		)
		);
	tableWidget.exec();*/
	//show();
}
