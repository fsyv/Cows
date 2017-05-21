#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RealTimeCurveQChartWidget;

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
private:
	void signalConnect();

    Ui::MainWindow *ui;

	RealTimeCurveQChartWidget *cw;

	QList<qreal> t, x, y, z;
};

#endif // MAINWINDOW_H
