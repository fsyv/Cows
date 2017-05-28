#include "stdafx.h"

#include "mainwidget.h"
#include "ui_mainwindow.h"
#include "AboutDialog.h"
#include "listdatawidget.h"
#include "sqlexecute.h"
#include "RealTimeCurveQChartWidget.h"
#include "pieserieswidget.h"

#include "comdialog.h"

#include "comdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Cows");

    signalConnect();

    //移除一个多余的没有用的窗体
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));

    cw = new RealTimeCurveQChartWidget;
    ui->stackedWidget->addWidget(cw);



    ldw = new ListDataWidget;
    ui->stackedWidget->addWidget(ldw);

    ui->stackedWidget->setCurrentIndex(1);

    ComDialog comdialog;
    comdialog.exec();

    m_pComData = new ComData(comdialog.getSerialPort());
    connect(m_pComData, &ComData::dataRecv, this, &MainWindow::recvData);
    m_pComData->start();

//    m_pComData = new ComData(nullptr);
//    connect(m_pComData, &ComData::dataRecv, this, &MainWindow::recvData);
//    m_pComData->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(rorwResult.size())
    {
        //数据没有导出
        QMessageBox::StandardButton button =
                QMessageBox::question(nullptr, "提示", "是否保存当前数据？", (QMessageBox::Yes | QMessageBox::No | QMessageBox ::Cancel));
        if (QMessageBox::Yes == button)
        {
            bool ok;
            exportData(ok);
            if(ok)
                QMainWindow::closeEvent(e);
            else
                e->ignore();
        }
        else if(QMessageBox::No == button)
        {
            rorwResult.clear();
            QMainWindow::closeEvent(e);
        }
        else
        {
            e->ignore();
        }
    }
    else
    {
        QMainWindow::closeEvent(e);
    }
}

void MainWindow::signalConnect()
{
    /*********************QAction*************************/
    //显示Qt版权说明
    connect(ui->action_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

    //退出
    connect(ui->action_exit, &QAction::triggered, qApp, &QApplication::exit);

    //显示关于
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAbout);


    /*********************QToolButton*************************/
    connect(ui->action_showchart, &QAction::triggered, this, &MainWindow::showChart);
    connect(ui->action_history, &QAction::triggered, this, &MainWindow::showHistory);

    //导出数据action
    connect(ui->action_export, SIGNAL(triggered(bool)), this, SLOT(exportData()));
    //导入数据action
    connect(ui->action_import, &QAction::triggered, this, &MainWindow::importData);
    //分析数据
    connect(ui->action_analysis, &QAction::triggered, this, &MainWindow::analysisData);
}

int MainWindow::calculatData(const QList<qreal> &z)
{
    QList<qreal> s = Matlab::NorAverageSequence(z);
    Matlab::ForwardDifference(s);
    QList<real_t> a = Matlab::AnalysisCredibilityDependS(Matlab::CalcStandardDeviation(s));
    QList<real_t> b = Matlab::AnalysisCredibilityDependRange(Matlab::CalcRange(s));
    QList<real_t> c = Matlab::AnalysisCredibilityDependKurtosis(Matlab::CalcKurtosis(s));
    QList<real_t> d = Matlab::DS_fusion(Matlab::DS_fusion(a, b), Matlab::DS_fusion(a, c));

    //需要保存的状态
    return Matlab::CalcCowState(d);
}

void MainWindow::showChart()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showAbout()
{
    AboutDialog *about = new AboutDialog(this);
    about->setModal(true);
    about->show();
}

void MainWindow::showHistory()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::exportData()
{
    bool ok = false;
    m_pComData->stop();
loop:
    QString name = QInputDialog::getText(nullptr, "保存数据", "请输入保存的名字：", QLineEdit::Normal, QString(), &ok);

    if (ok)
    {
        QString table = QString("%1_%2").arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(name);

        if (SQLExecute::getAllTableName().contains(table))
        {
            //保存的表中已经包含了这个表
            if (QMessageBox::Cancel == QMessageBox::question(nullptr, "提示", "名字已经存在，是否追加数据？"))
            {
                //大返回
                goto loop;
            }
        }
        SQLExecute::exportData(table, rorwResult);
        rorwResult.clear();
        QMessageBox::information(nullptr, "提示", "导出成功！");
    }
    else
    {
        m_pComData->start();
    }
}

void MainWindow::importData()
{

}

void MainWindow::analysisData()
{
    PieSeriesWidget w;
    w.setValue(rorwResult);
    w.resize(size() * 0.618);
    w.exec();
}

void MainWindow::recvData(quint32 tick, qreal x, qreal y, qreal z)
{
    cw->dataReceived(x, y, z);

    if(tick % 50 == 0 && tick > 0)
    {
        rorwResult.append(calculatData(zs));
        zs.clear();
    }

    zs.append(z);
}


void MainWindow::exportData(bool &ok)
{
    m_pComData->stop();
loop:
    QString name = QInputDialog::getText(nullptr, "保存数据", "请输入保存的名字：", QLineEdit::Normal, QString(), &ok);

    if (ok)
    {
        QString table = QString("%1_%2").arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(name);

        if (SQLExecute::getAllTableName().contains(table))
        {
            //保存的表中已经包含了这个表
            if (QMessageBox::Cancel == QMessageBox::question(nullptr, "提示", "名字已经存在，是否追加数据？"))
            {
                //大返回
                goto loop;
            }
        }

        SQLExecute::exportData(table, rorwResult);
        rorwResult.clear();
    }
    else
    {
        m_pComData->start();
    }
}
