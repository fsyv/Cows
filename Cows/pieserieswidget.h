#ifndef PIESERIESWIDGET_H
#define PIESERIESWIDGET_H

#include <QWidget>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QHBoxLayout>
#include <QTimer>
using namespace QtCharts;

class PieSeriesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieSeriesWidget(QWidget *parent = 0);

    void setValue(qreal value1, qreal value2, qreal value3);

signals:

public slots:

private:
    QPieSeries *series;
    QPieSlice *slice0;
    QPieSlice *slice1;
    QPieSlice *slice2;
    QChart *chart;
    QChartView *chartView;
};

#endif // PIESERIESWIDGET_H
