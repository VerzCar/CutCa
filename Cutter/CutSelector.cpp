#include "CutSelector.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>
#include <QDebug>

CutSelector::CutSelector(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), _isMouseClicked(false)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(QApplication::desktop()->geometry());

    QApplication::setOverrideCursor(QCursor(QPixmap("Zeichnung.svg")));
    //setCursor(Qt::CursorShape::CrossCursor);
setStyleSheet("color: white;");
    setMouseTracking(true);

    _desktopPixmap = grabScreenshot();
    _desktopImage = _desktopPixmap.toImage();
}

CutSelector::~CutSelector()
{
    //setCursor(Qt::CursorShape::LastCursor);
    QApplication::restoreOverrideCursor();
    setMouseTracking(false);
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
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        _isMouseClicked = true;
    _selectedRect.setTopLeft(event->globalPos());
    }
}

void CutSelector::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        _isMouseClicked = false;
    _selectedPixmap = _desktopPixmap.copy(_selectedRect.normalized());
    accept();
        }
}

void CutSelector::mouseMoveEvent(QMouseEvent* event)
{
    if(_isMouseClicked)
    {
    _selectedRect.setBottomRight(event->globalPos());
    update();
    }

        qDebug() << "event->globalPos() " <<     _desktopImage.pixel(event->pos());


}

void CutSelector::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawPixmap(0, 0, _desktopPixmap);

    QPainterPath path;
    path.addRect(rect());
    path.addRect(_selectedRect);
    p.fillPath(path, QColor::fromRgb(255, 255, 255, 100));

    p.setPen(Qt::red);
    p.drawRect(_selectedRect);
}

const QPixmap& CutSelector::getCroppedSelection()
{
    return _selectedPixmap;
}
