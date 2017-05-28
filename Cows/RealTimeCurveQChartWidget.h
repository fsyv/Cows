#ifndef REALTIMECURVEQCHARTWIDGET_H
#define REALTIMECURVEQCHARTWIDGET_H

#include <QWidget>
#include <QList>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChartView>
#include <QValueAxis>

using namespace QtCharts;

class RealTimeCurveQChartWidget : public QWidget {
	Q_OBJECT
public:
	explicit RealTimeCurveQChartWidget(QWidget *parent = 0);
	~RealTimeCurveQChartWidget();
	/**
	* ���յ�����Դ�����������ݣ�����Դ������λ�����ɼ������������ȡ�
	*/
    void dataReceived(qreal x, qreal y, qreal z);

private:
	void getMinMax(const qreal currentValue, qreal &min, qreal &max);
	
	int maxSize;  // data ���洢 maxSize ��Ԫ��
	int maxValue; // ҵ�����ݵ����ֵ
	QList<qreal> data[3];
	QChart *chart;
	QChartView *chartView;
	
	QLineSeries *lineSeriesX;
	QLineSeries *lineSeriesY;
	QLineSeries *lineSeriesZ;

	QScatterSeries *scatterSeries;
	QValueAxis *axisX;
	QValueAxis *axisY;
};
#endif // REALTIMECURVEQCHARTWIDGET_H
