#pragma once
#pragma  execution_character_set("utf-8")

#include <QDialog>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QHBoxLayout>
#include <QTimer>
using namespace QtCharts;

class PieSeriesWidget : public QDialog
{
    Q_OBJECT
public:
    explicit PieSeriesWidget(QWidget *parent = 0);

    void setValue(int value1, int value2, int value3);
    void setValue(const QList<int> &value);

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

