#pragma once
#pragma  execution_character_set("utf-8")
#include "qchartview.h"
#include <QtCharts>

class ChartWidget :
	public QChartView
{
	Q_OBJECT
public:
	ChartWidget(QWidget *parent = Q_NULLPTR);
	~ChartWidget();

	void addSeries(const QList<QPointF> &points, const QString &name);

	void setXTitle(const QString &);
	void setYTitle(const QString &);
	void setTitle(const QString &);

private:

	void loadChart();

	QChart *chart;
	QValueAxis *axisX;
	QValueAxis *axisY;

	QString xTitle;
	QString yTitle;
	QString title;
};

