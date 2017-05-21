#include "comdialog.h"
#include "ui_comdialog.h"

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
}

ComDialog::~ComDialog()
{
    delete ui;
}

void ComDialog::closeEvent(QCloseEvent *e)
{
    exit(0);
}

void ComDialog::on_okButton_clicked()
{

}

void ComDialog::on_closeButton_clicked()
{
    exit(0);
}
