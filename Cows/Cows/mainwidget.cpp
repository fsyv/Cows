#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "mainwidget.h"
#include "ChartWidget.h"

using namespace QtCharts;

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	ChartWidget *chartWidget = new ChartWidget(this);
	qreal  array[51] = { 0, -0.14, -0.06, 0.05, -0.09, 0.36, 0.36,
		-0.08, -0.27, -0.62, 0.03, 0.04, 0.19, 0.27, -0.06,-0.01,-0.37,0.16,
		-0.27,0.12, 0.2,0.1,0.3, 0.22,0.12,0.02,0.2,
		0.58,0.08,-0.05,-0.01,-0.74,0.23,0.03,
		0.02, -0.06, -0.31, 0.27, 0.11, -0.08, -0.33, 0.34, 0.02,
		0.16, 0.34, 0.02, 0.16, 0.01, -0.09, 0.02, -0.35 };

	QList<QPointF> list1, list2;
	for (int i = 1; i < 51; ++i)
	{
		QPointF p;
		p.setX(i);
		p.setY(array[i]);
		list1.append(p);
	}

	for (int i = 1; i < 51; ++i)
	{
		QPointF p;
		p.setX(i - 1);
		p.setY(array[i]);
		list2.append(p);
	}
	chartWidget->addSeries(list1, "X方向");
	chartWidget->addSeries(list2, "Y方向");
	chartWidget->setXTitle("横坐标");
	chartWidget->setYTitle("纵坐标");
	chartWidget->setTitle("ChartDemo");


	chartWidget->resize(1000, 600);

}
