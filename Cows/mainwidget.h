#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

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

protected:
    void closeEvent(QCloseEvent *e);

protected slots:
	void showChart();
	void showAbout();
	void showHistory();
	void exportData();
    void importData();
    void analysisData();
    void recvData(quint32 tick, qreal x, qreal y, qreal z);
private:
    void exportData(bool &ok);
	void signalConnect();
    int calculatData(const QList<qreal> &z);

    Ui::MainWindow *ui;

	RealTimeCurveQChartWidget *cw;
    ListDataWidget *ldw;
    ComData *m_pComData;

    //true为跑，false为走
    QList<int> rorwResult;
    QList<qreal> zs;
};

#endif // MAINWINDOW_H
