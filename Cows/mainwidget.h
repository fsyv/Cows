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

protected:
	void timerEvent(QTimerEvent *e);

protected slots:
	void showChart();
	void showAbout();
	void showHistory();
	void exportData();
private:

	void signalConnect();

    Ui::MainWindow *ui;

	TableWidget *tw;
};

#endif // MAINWINDOW_H
