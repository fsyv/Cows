#include "stdafx.h"

#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
	: QDialog(parent)
{

}

TableWidget::~TableWidget()
{
    delete m_pModel;
    delete m_pTableView;
    delete m_pChart;
    delete m_pChartView;
    delete m_pSeriesX;
    delete m_pSeriesY;
    delete m_pSeriesZ;
}

CustomTableModel *TableWidget::getTableModel()
{
    return m_pModel;
}

void TableWidget::addData(const QList<qreal> &t, const QList<qreal> &x, const QList<qreal> &y, const QList<qreal> &z)
{
    m_pModel = new CustomTableModel;
    m_pModel->addData(t, x, y, z);
    m_pTableView = new QTableView;
    m_pTableView->setModel(m_pModel);
    m_pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_pChart = new QChart;
    m_pChart->setAnimationOptions(QChart::AllAnimations);

    //axisX = new QValueAxis;
    //axisX->setRange(0, 50);
    //axisX->setTickCount(51);
    //axisX->setLabelFormat("%d");

    //axisY = new QValueAxis;
    //axisY->setRange(-50.0, 50.0);
    //axisY->setTickCount(9);
    //axisY->setLabelFormat("%.2f");

    //m_pChart->addAxis(axisX, Qt::AlignBottom);
    //m_pChart->addAxis(axisY, Qt::AlignLeft);

    initAxis();

    m_pChart->createDefaultAxes();
    m_pChartView = new QChartView(m_pChart);
    m_pChartView->setRenderHint(QPainter::Antialiasing);
    m_pChartView->setMinimumSize(640, 480);

    m_pGridLayout = new QGridLayout;
    m_pGridLayout->addWidget(m_pTableView, 1, 0);
    m_pGridLayout->addWidget(m_pChartView, 1, 1);
    m_pGridLayout->setColumnStretch(1, 1);
    m_pGridLayout->setColumnStretch(0, 0);
    setLayout(m_pGridLayout);
}

void TableWidget::initAxis()
{
	// XÇúÏß
	m_pSeriesX = new QSplineSeries;
	m_pSeriesX->setName("X");
	QVXYModelMapper *mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(1);
	mapper->setSeries(m_pSeriesX);
	mapper->setModel(m_pModel);
	
	m_pChart->addSeries(m_pSeriesX);
	//m_pChart->setAxisX(axisX, m_pSeriesX);
	//m_pChart->setAxisY(axisY, m_pSeriesX);

	

	QString seriesColorHex = "#000000";

	// get the color of the series and use it for showing the mapped area
	seriesColorHex = "#" + QString::number(m_pSeriesX->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(1, 0, 1, m_pModel->rowCount()));

	// YÇúÏß
	m_pSeriesY = new QSplineSeries;
	m_pSeriesY->setName("Y");

	mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(2);
	mapper->setSeries(m_pSeriesY);
	mapper->setModel(m_pModel);
	m_pChart->addSeries(m_pSeriesY);
	//m_pChart->setAxisX(axisX, m_pSeriesY);
	//m_pChart->setAxisY(axisY, m_pSeriesY);
	

	seriesColorHex = "#" + QString::number(m_pSeriesY->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(2, 0, 1, m_pModel->rowCount()));

	// ZÇúÏß
	m_pSeriesZ = new QSplineSeries;
	m_pSeriesZ->setName("Z");

	mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(3);
	mapper->setSeries(m_pSeriesZ);
	mapper->setModel(m_pModel);
	m_pChart->addSeries(m_pSeriesZ);
	//m_pChart->setAxisX(axisX, m_pSeriesZ);
	//m_pChart->setAxisY(axisY, m_pSeriesZ);

	seriesColorHex = "#" + QString::number(m_pSeriesZ->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(3, 0, 1, m_pModel->rowCount()));
}

