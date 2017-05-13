/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "tablewidget.h"
#include "customtablemodel.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtWidgets/QHeaderView>

QT_CHARTS_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    //! [1]
    CustomTableModel *model = new CustomTableModel;
    //! [1]

    //! [2]
    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //! [2]

    //! [3]
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // XÇúÏß
    QSplineSeries *series_x = new QSplineSeries;
	series_x->setName("X");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
	mapper->setSeries(series_x);
    mapper->setModel(model);
	chart->addSeries(series_x);

    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
	seriesColorHex = "#" + QString::number(series_x->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(1, 0, 1, model->rowCount()));

    // YÇúÏß
	QSplineSeries *series_y = new QSplineSeries;
	series_y->setName("Y");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(2);
	mapper->setSeries(series_y);
    mapper->setModel(model);
	chart->addSeries(series_y);

	seriesColorHex = "#" + QString::number(series_y->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 1, model->rowCount()));

	// ZÇúÏß
	QSplineSeries *series_z = new QSplineSeries;
	series_z->setName("Z");

	mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(3);
	mapper->setSeries(series_z);
	mapper->setModel(model);
	chart->addSeries(series_z);

	seriesColorHex = "#" + QString::number(series_z->pen().color().rgb(), 16).right(6).toUpper();
	model->addMapping(seriesColorHex, QRect(3, 0, 1, model->rowCount()));

    //! [8]
    chart->createDefaultAxes();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    //! [8]

    //! [9]
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [9]
}
