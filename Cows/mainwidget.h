#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TableWidget;

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

    void loadExcel(QList<qreal> &t, QList<qreal> &x, QList<qreal> &y, QList<qreal> &z);
    void calculatData(QList<qreal> &t, QList<qreal> &x, QList<qreal> &y, QList<qreal> &z);

    Ui::MainWindow *ui;

	TableWidget *tw;
};

#endif // MAINWINDOW_H
