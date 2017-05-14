#pragma once
#pragma  execution_character_set("utf-8")

#include <QWidget>

namespace Ui {
class ListDataWidget;
}

class ListDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListDataWidget(QWidget *parent = 0);
    ~ListDataWidget();

private:
	void loadData();

    Ui::ListDataWidget *ui;
};
