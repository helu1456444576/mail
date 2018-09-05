#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:blue");
}

Dialog3::~Dialog3()
{
    delete ui;
}
