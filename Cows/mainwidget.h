#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
	void showChart();
	void showAbout();
private:

	void signalConnect();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
