#pragma once
#pragma  execution_character_set("utf-8")

#include <QDialog>

QT_BEGIN_NAMESPACE

class CustomTableModel;
class QGridLayout;
class QTableView;

namespace QtCharts{
	class QChart;
	class QChartView;
	class QSplineSeries;
	class QVXYModelMapper;
	class QValueAxis;
}

using namespace QtCharts;

class TableWidget : public QDialog
{
    Q_OBJECT
public:
    TableWidget(QWidget *parent = 0);
    ~TableWidget();

	CustomTableModel *getTableModel();
    void addData(const QList<qreal> &t, const QList<qreal> &x, const QList<qreal> &y, const QList<qreal> &z);

    void calculatData(const QList<qreal> &z);

//protected:
//	void showEvent(QShowEvent *e);

private:
	void initAxis();
	void destroyAxis();

	CustomTableModel *m_pModel;
	QChart *m_pChart;
	QTableView *m_pTableView;
	QChartView *m_pChartView;
	QSplineSeries *m_pSeriesX;
	QSplineSeries *m_pSeriesY;
	QSplineSeries *m_pSeriesZ;
	QGridLayout *m_pGridLayout;
	//QValueAxis *axisX;
	//QValueAxis *axisY;
};

QT_END_NAMESPACE
