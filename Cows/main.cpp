#include <QApplication>
#include "tablewidget.h"
//#include "mainwidget.h"
#include "listdatawidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListDataWidget w;
//    MainWindow w;
//	AboutDialog w;
	w.show();

    return a.exec();
}
