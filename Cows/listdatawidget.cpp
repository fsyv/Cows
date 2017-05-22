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
    SQLExecute::importData(
                ui->listWidget->item(index.row())->text()
                );
    //show();
}

void ListDataWidget::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* curItem = ui->listWidget->itemAt( pos );

    if( curItem == nullptr )
        return;

    QMenu *popMenu = new QMenu( this );
    QAction *deleteSeed = new QAction(tr("删除"), this);
    popMenu->addAction( deleteSeed );
    connect( deleteSeed, SIGNAL(triggered() ), this, SLOT(deleteSeedSlot()));
    popMenu->exec(QCursor::pos());
    delete popMenu;
    delete deleteSeed;
}

void ListDataWidget::deleteSeedSlot()
{
    QListWidgetItem * item = ui->listWidget->currentItem();
    if( item == nullptr )
        return;

    if(QMessageBox::Yes == QMessageBox::question(nullptr, "提示", "删除这条记录？"))
    {
        SQLExecute::deleteTable(item->text());

        ui->listWidget->takeItem(ui->listWidget->currentIndex().row());
    }
}
