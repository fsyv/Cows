#pragma once
#include "qdialog.h"

class QLabel;
class QPushButton;

class AboutDialog :
	public QDialog
{
	Q_OBJECT
public:
	AboutDialog(QWidget *parent = Q_NULLPTR);
	~AboutDialog();



private:

	void setContent();

	QLabel *showpixmap;
	QPushButton *ok;
	QLabel *information;
};

