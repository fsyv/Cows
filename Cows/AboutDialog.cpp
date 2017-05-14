#pragma once
#pragma  execution_character_set("utf-8")
#include "AboutDialog.h"
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent)
{

	setWindowTitle("关于奶牛运动监测系统");

	showpixmap = new QLabel(this);
	ok = new QPushButton("关闭", this);
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
	QString text = "<h1>奶牛运动监测系统</h1><\br>"\
					"<p>版本号0.1.1</p><\br>"\
					"<p>用于将奶牛的运动数据通过图表的方式展示出来</p><\br>"\
					"<p>CopyRight (C) 长沙理工大学</p>";

	information->setText(text);

	connect(ok, &QPushButton::clicked, this, &QDialog::close);
}