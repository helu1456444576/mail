#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:red");
}

Dialog1::~Dialog1()
{
    delete ui;
}