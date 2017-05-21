#include <QApplication>
#include "mainwidget.h"
#include "listdatawidget.h"
#include "RealTimeCurveQChartWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//  ListDataWidget w;
    MainWindow w;
//	AboutDialog w;
//	RealTimeCurveQChartWidget w;
	w.show();


    return a.exec();
}
