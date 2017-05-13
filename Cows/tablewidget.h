#pragma once
#pragma  execution_character_set("utf-8")

#include <QWidget>

QT_BEGIN_NAMESPACE

class CustomTableModel;
class QGridLayout;
class QTableView;

namespace QtCharts{
	class QChart;
	class QChartView;
	class QSplineSeries;
	class QVXYModelMapper;
}

using namespace QtCharts;

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    TableWidget(QWidget *parent = 0);

private:
	void initAxis();

	CustomTableModel *m_pModel;
	QChart *m_pChart;
	QTableView *m_pTableView;
	QChartView *m_pChartView;
	QSplineSeries *m_pSeriesX;
	QSplineSeries *m_pSeriesY;
	QSplineSeries *m_pSeriesZ;
	QGridLayout *m_pGridLayout;
};

QT_END_NAMESPACE