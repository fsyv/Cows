#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    Ui::MainWindow *ui;

	RealTimeCurveQChartWidget *cw;
    ListDataWidget *ldw;
    ComData *m_pComData;

	QList<qreal> t, x, y, z;
};

#endif // MAINWINDOW_H
