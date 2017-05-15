#include "mainwidget.h"
#include "ui_mainwindow.h"
#include "tablewidget.h"
#include "AboutDialog.h"
#include "listdatawidget.h"
#include <QLabel>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	signalConnect();

	

	//移除一个多余的没有用的窗体
	ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));

	TableWidget *tw = new TableWidget;
	ui->stackedWidget->addWidget(tw);

	ListDataWidget *ldw = new ListDataWidget;
	ui->stackedWidget->addWidget(ldw);

	ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signalConnect()
{
	/*********************QAction*************************/
	//显示Qt版权说明
	connect(ui->action_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
	
	//退出
	connect(ui->action_exit, &QAction::triggered, qApp, &QApplication::exit);

	//显示关于
	connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAbout);


	/*********************QToolButton*************************/
	connect(ui->toolButton_chart, &QToolButton::clicked, this, &MainWindow::showChart);
	connect(ui->pushButton_history, &QPushButton::clicked, this, &MainWindow::showHistory);
}

void MainWindow::showChart()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showAbout()
{
	AboutDialog *about = new AboutDialog(this);
	about->setModal(true);
	about->show();
}

void MainWindow::showHistory()
{
	ui->stackedWidget->setCurrentIndex(2);
}