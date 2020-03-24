#include "CutSelector.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>

CutSelector::CutSelector(QWidget *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(QApplication::desktop()->geometry());

    _desktopPixmap = grabScreenshot();
}


QPixmap CutSelector::grabScreenshot()
{
    QPixmap desktopPixmap = QPixmap(QApplication::desktop()->geometry().size());
    QPainter p(&desktopPixmap);

    for (QScreen* screen : QApplication::screens())
    {
        p.drawPixmap(screen->geometry().topLeft(), screen->grabWindow(0));
    }

    return desktopPixmap;
}

void CutSelector::mousePressEvent(QMouseEvent* event)
{
    _selectedRect.setTopLeft(event->globalPos());
}

void CutSelector::mouseReleaseEvent(QMouseEvent *)
{
    selectedPixmap = _desktopPixmap.copy(_selectedRect.normalized());
    accept();
}

void CutSelector::mouseMoveEvent(QMouseEvent *event)
{
    _selectedRect.setBottomRight(event->globalPos());
    update();
}

void CutSelector::paintEvent(QPaintEvent *)
{
    QPainter p (this);
    p.drawPixmap(0, 0, _desktopPixmap);

    QPainterPath path;
    path.addRect(rect());
    path.addRect(_selectedRect);
    p.fillPath(path, QColor::fromRgb(255,255,255,200));

    p.setPen(Qt::red);
    p.drawRect(_selectedRect);
}
