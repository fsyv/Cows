#include "pieserieswidget.h"

PieSeriesWidget::PieSeriesWidget(QWidget *parent) : QWidget(parent)
{
    series = new QPieSeries();
    series->append("运动状态", 1);
    series->append("行走状态", 1);
    series->append("未知", 1);


    slice0 = series->slices().at(0);
    slice0->setBrush(Qt::red);

    slice1 = series->slices().at(1);
    slice1->setBrush(Qt::green);

    slice2 = series->slices().at(2);
    slice2->setBrush(Qt::yellow);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("运动状态");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(chartView);
    setLayout(layout);

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this](){
        setValue(qrand() % 20, qrand() % 20, qrand() % 20);
    });

    timer->start(2000);
}

void PieSeriesWidget::setValue(qreal value1, qreal value2, qreal value3)
{
    slice0->setValue(value1);
    slice1->setValue(value2);
    slice2->setValue(value3);
}
