#include "Cutter.h"
#include "ui_Cutter.h"
#include "CutSelector.h"

Cutter::Cutter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cutter)
{
    ui->setupUi(this);
}

Cutter::~Cutter()
{
    delete ui;
}

void Cutter::on_btnCapture_clicked()
{
    CutSelector selector;
    selector.exec();
}
