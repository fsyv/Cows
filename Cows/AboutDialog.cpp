#pragma once
#pragma  execution_character_set("utf-8")
#include "AboutDialog.h"
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent)
{

	setWindowTitle("������ţ�˶����ϵͳ");

	showpixmap = new QLabel(this);
	ok = new QPushButton("�ر�", this);
	information = new QLabel(this);

	setFixedSize(466, 236);

	setContent();
}


AboutDialog::~AboutDialog()
{
}

void AboutDialog::setContent()
{
	showpixmap->move(50, 50);
	showpixmap->setPixmap(QPixmap(":/Cows.ico"));

	ok->move(365, 190);

	information->move(150, 20);
	QString text = "<h1>��ţ�˶����ϵͳ</h1><\br>"\
					"<p>�汾��0.1.1</p><\br>"\
					"<p>���ڽ���ţ���˶�����ͨ��ͼ��ķ�ʽչʾ����</p><\br>"\
					"<p>CopyRight (C) ��ɳ����ѧ</p>";

	information->setText(text);

	connect(ok, &QPushButton::clicked, this, &QDialog::close);
}