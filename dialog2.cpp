#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:yellow");
}

Dialog2::~Dialog2()
{
    delete ui;
}
