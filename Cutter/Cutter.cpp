#include "Cutter.h"
#include "ui_Cutter.h"
#include "CutSelector.h"
#include <QDebug>

Cutter::Cutter(QWidget* parent)
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

    if (selector.exec() == QDialog::Accepted)
    {
        _currentCroppedSelection = selector.getCroppedSelection();
        emit cutted();
    }
}

bool Cutter::hasCroppedPixmap()
{
    return _currentCroppedSelection.isNull();
}

const QPixmap* Cutter::getCroppedPixmap()
{
    return &_currentCroppedSelection;
}
