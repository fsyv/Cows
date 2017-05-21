#ifndef REALTIMECURVEQCHARTWIDGET_H
#define REALTIMECURVEQCHARTWIDGET_H

#include <QWidget>
#include <QList>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
using namespace QtCharts;
class RealTimeCurveQChartWidget : public QWidget {
	Q_OBJECT
public:
	explicit RealTimeCurveQChartWidget(QWidget *parent = 0);
	~RealTimeCurveQChartWidget();
protected:
	void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
private:
	/**
	* ���յ�����Դ�����������ݣ�����Դ������λ�����ɼ������������ȡ�
	*/
	void dataReceived(qreal value);
	int timerId;
	int maxSize;  // data ���洢 maxSize ��Ԫ��
	int maxValue; // ҵ�����ݵ����ֵ
	QList<qreal> data; // �洢ҵ�����ݵ� list
	QChart *chart;
	QChartView *chartView;
	QSplineSeries *splineSeries;
	QScatterSeries *scatterSeries;
};
#endif // REALTIMECURVEQCHARTWIDGET_H