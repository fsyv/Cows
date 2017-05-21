#pragma  execution_character_set("utf-8")
#include "RealTimeCurveQChartWidget.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QDebug>
RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(QWidget *parent) : QWidget(parent) {
	maxSize = 50;  
	maxValue = 200;
	timerId = startTimer(300);
	qsrand(QDateTime::currentDateTime().toTime_t());
	

	chart = new QChart();
	chart->setTitle("实时动态曲线");

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
	for (int i = 0; i < maxSize; ++i) {
		lineSeriesX->append(i, 0);
	}

	lineSeriesY = new QLineSeries();
	for (int i = 0; i < maxSize; ++i) {
		lineSeriesY->append(i, 0);
	}

	lineSeriesZ = new QLineSeries();
	for (int i = 0; i < maxSize; ++i) {
		lineSeriesZ->append(i, 0);
	}

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

	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);

	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(chartView);
	setLayout(layout);

}
RealTimeCurveQChartWidget::~RealTimeCurveQChartWidget() {
}

void RealTimeCurveQChartWidget::timerEvent(QTimerEvent *event) {
	if (event->timerId() == timerId) {
		qreal newData = (qrand() % maxValue - 100) * 0.01;
		//dataReceived(newData);
		qDebug() << newData;
	}
}

void RealTimeCurveQChartWidget::dataReceived(qreal x, qreal y, qreal z) {
	data[0] << x;
	data[1] << y;
	data[2] << z;
	while (data[0].size() > maxSize) {
		data[0].removeFirst();
		data[1].removeFirst();
		data[2].removeFirst();
	}
	if (isVisible()) {
		int delta = maxSize - data[0].size();
		for (int i = 0; i < data[0].size(); ++i) {
			lineSeriesX->replace(delta + i, lineSeriesX->at(delta + i).x(), data[0].at(i));
			lineSeriesY->replace(delta + i, lineSeriesY->at(delta + i).x(), data[1].at(i));
			lineSeriesZ->replace(delta + i, lineSeriesZ->at(delta + i).x(), data[2].at(i));
		}
	}
}