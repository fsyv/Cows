
#include <QApplication>
#include "tablewidget.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//	AboutDialog w;
	w.show();

    return a.exec();
}
