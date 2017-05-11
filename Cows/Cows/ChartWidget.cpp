#include "stdafx.h"
#include "ChartWidget.h"


ChartWidget::ChartWidget(QWidget *parent) : QChartView(parent)
{
	loadChart();
	
	setChart(chart);
	setRenderHint(QPainter::Antialiasing);
}


ChartWidget::~ChartWidget()
{
	delete chart;
	delete axisX;
	delete axisY;
}

void ChartWidget::addSeries(const QList<QPointF> &points, const QString &name)
{
	QLineSeries* series = new QLineSeries();

	series->append(points);
	series->setName(name);
	chart->addSeries(series);

	chart->setAxisX(axisX, series);
	chart->setAxisY(axisY, series);
}


void ChartWidget::loadChart()
{
	chart = new QChart();
	chart->legend()->setVisible(true);
	chart->createDefaultAxes();
	chart->legend()->setAlignment(Qt::AlignBottom);
	

	axisX = new QValueAxis;
	axisX->setRange(1, 50);
	axisX->setTickCount(25);
	axisX->setLabelFormat("%d");

	axisY = new QValueAxis;
	axisY->setRange(-1.0, 1.0);
	axisY->setTickCount(7);
	axisY->setLabelFormat("%.2f");
}

void ChartWidget::setXTitle(const QString &title)
{
	axisX->setTitleText(title);
}
void ChartWidget::setYTitle(const QString &title)
{
	axisY->setTitleText(title);
}

void ChartWidget::setTitle(const QString &title)
{
	chart->setTitle(title);
}