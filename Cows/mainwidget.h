#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "cowsstate.h"

namespace Ui {
class MainWindow;
}

class RealTimeCurveQChartWidget;
class ListDataWidget;
class ComData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
	void showChart();
	void showAbout();
	void showHistory();
	void exportData();
    void importData();
    void recvData(quint32 tick, qreal x, qreal y, qreal z);
private:
	void signalConnect();
    CowsState::State calculatData(const QList<qreal> &z);

    Ui::MainWindow *ui;

	RealTimeCurveQChartWidget *cw;
    ListDataWidget *ldw;
    ComData *m_pComData;

    QList<CowsState> rorwResult;
    QMap<char, QList<qreal> * > m_data;
    QList<qreal> zs;
};

#endif // MAINWINDOW_H
