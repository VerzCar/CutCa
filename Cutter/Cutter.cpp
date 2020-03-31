#include "Cutter.h"
#include "ui_Cutter.h"
#include "CutSelector.h"
#include <QDebug>
#include <QThread>

Cutter::Cutter(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Cutter)
{
    ui->setupUi(this);

    setStyleSheet("QPushButton#btnCapture { background-color: #404142; \
                  border-radius: 50%; border-width: 2px; border-color: beige; } \
                QPushButton#btnCapture:pressed { background-color: red; } \
                QPushButton#btnCapture:hover { background-color: beige; border-color: #404142;}");

}

Cutter::~Cutter()
{
    delete ui;
}

void Cutter::on_btnCapture_clicked()
{
    hide();

    //wait until the dialog is hide, otherwise it will be in the capture
    QThread::msleep(200);

    CutSelector selector;

    int result = selector.exec();
    if (result == QDialog::Accepted)
    {
        _currentCroppedSelection = selector.getCroppedSelection();
        emit cutted();
        show();
    }
    else if(result == QDialog::Rejected)
    {
        show();
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

