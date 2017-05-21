#pragma  execution_character_set("utf-8")
#include "RealTimeCurveQChartWidget.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QDebug>
RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(QWidget *parent) : QWidget(parent) {
    maxSize = 50;
    maxValue = 200;

    chart = new QChart();
    chart->setTitle("采集到的加速器");

    axisX = new QValueAxis;
    axisX->setRange(0, 50);
    axisX->setTickCount(51);
    axisX->setLabelFormat("%d");

    axisY = new QValueAxis;
    axisY->setRange(-5.0, 5.0);
    axisY->setTickCount(9);
    axisY->setLabelFormat("%.2f");

    chart->createDefaultAxes();


    lineSeriesX = new QLineSeries();

    lineSeriesY = new QLineSeries();

    lineSeriesZ = new QLineSeries();

    lineSeriesX->setName("x轴");
    lineSeriesY->setName("y轴");
    lineSeriesZ->setName("z轴");

    chart->addSeries(lineSeriesX);
    chart->setAxisX(axisX, lineSeriesX);
    chart->setAxisY(axisY, lineSeriesX);

    chart->addSeries(lineSeriesY);
    chart->setAxisX(axisX, lineSeriesY);
    chart->setAxisY(axisY, lineSeriesY);

    chart->addSeries(lineSeriesZ);
    chart->setAxisX(axisX, lineSeriesZ);
    chart->setAxisY(axisY, lineSeriesZ);

//    chart->addAxis(axisX, Qt::AlignBottom);
//    chart->addAxis(axisY, Qt::AlignLeft);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    setLayout(layout);
}
RealTimeCurveQChartWidget::~RealTimeCurveQChartWidget() {
}

void RealTimeCurveQChartWidget::dataReceived(qreal x, qreal y, qreal z) {
	data[0] << x;
	data[1] << y;
	data[2] << z;

	if (lineSeriesX->count() < 50)
	{
		lineSeriesX->append(lineSeriesX->count(), x);
		lineSeriesY->append(lineSeriesZ->count(), y);
		lineSeriesZ->append(lineSeriesZ->count(), z);
	}
	else
	{
		while (data[0].size() > maxSize) {
			data[0].removeFirst();
			data[1].removeFirst();
			data[2].removeFirst();
		}
		if (isVisible()) {
			int delta = maxSize - data[0].size();
			qreal min = data[0].at(0), max = 0.0;;
			for (int i = 0; i < data[0].size(); ++i) {
				lineSeriesX->replace(delta + i, lineSeriesX->at(delta + i).x(), data[0].at(i));
				getMinMax(data[0].at(i), min, max);
				lineSeriesY->replace(delta + i, lineSeriesY->at(delta + i).x(), data[1].at(i));
				getMinMax(data[1].at(i), min, max);
				lineSeriesZ->replace(delta + i, lineSeriesZ->at(delta + i).x(), data[2].at(i));
				getMinMax(data[2].at(i), min, max);
			}

			axisY->setRange(min, max);
		}
	}
}

void RealTimeCurveQChartWidget::getMinMax(const qreal currentValue, qreal &min, qreal &max)
{
	if (currentValue > max)
		max = currentValue;

	if (currentValue < min)
		min = currentValue;
}

