#pragma  execution_character_set("utf-8")
#include "RealTimeCurveQChartWidget.h"
#include <QDateTime>
#include <QHBoxLayout>
RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(QWidget *parent) : QWidget(parent) {
	maxSize = 31;   // ֻ�洢���µ� 31 ������
	maxValue = 99; // ���ݵ����ֵΪ 100����Ϊ�������ɵ������Ϊ [0, 100]
	timerId = startTimer(3000);
	qsrand(QDateTime::currentDateTime().toTime_t());
	splineSeries = new QSplineSeries();
	scatterSeries = new QScatterSeries();
	scatterSeries->setMarkerSize(8);
	// Ԥ�ȷ������꣬������ dataReceived ��ֱ���滻������
	for (int i = 0; i < maxSize; ++i) {
		splineSeries->append(i * 10, 0);
		scatterSeries->append(i * 10, 0);
	}
	chart = new QChart();
	chart->addSeries(splineSeries);
	chart->addSeries(scatterSeries);
	chart->legend();
	chart->setTitle("ʵʱ��̬����");
	chart->createDefaultAxes();
	chart->axisY()->setRange(-1, 1);
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
		// ģ�ⲻͣ�Ľ��յ�������
		qreal newData = (qrand() % (maxValue + 1)) * 0.01;
		dataReceived(newData);
	}
}
void RealTimeCurveQChartWidget::dataReceived(qreal value) {
	data << value;
	// ���ݸ���������ָ��ֵ����ɾ�����Ƚ��յ������ݣ�ʵ��������ǰ�ƶ�
	while (data.size() > maxSize) {
		data.removeFirst();
	}
	if (isVisible()) {
		// ���汻���غ��û�б�Ҫ�������ݵ�������
		// �滻��������������
		int delta = maxSize - data.size();
		for (int i = 0; i < data.size(); ++i) {
			splineSeries->replace(delta + i, splineSeries->at(delta + i).x(), data.at(i));
			scatterSeries->replace(delta + i, scatterSeries->at(delta + i).x(), data.at(i));
		}
	}
}