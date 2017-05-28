#include "pieserieswidget.h"

PieSeriesWidget::PieSeriesWidget(QWidget *parent) : QDialog(parent)
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
}

void PieSeriesWidget::setValue(int value1, int value2, int value3)
{
    slice0->setValue(value1);
    slice1->setValue(value2);
    slice2->setValue(value3);
}

void PieSeriesWidget::setValue(const QList<int> &value)
{
    int value1 = 0, value2 = 0, value3 = 0;

    for(const int &item : value)
    {
        switch (item) {
        case 0:
            //other
            value3++;
            break;
        case 1:
            //running
            value1++;
            break;
        case 2:
            //walk
            value2++;
            break;
        default:
            break;
        }
    }

    setValue(value1, value2, value3);
}
