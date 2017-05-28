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
	* 接收到数据源发送来的数据，数据源可以下位机，采集卡，传感器等。
	*/
    void dataReceived(qreal x, qreal y, qreal z);

private:
	void getMinMax(const qreal currentValue, qreal &min, qreal &max);
	
	int maxSize;  // data 最多存储 maxSize 个元素
	int maxValue; // 业务数据的最大值
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
