#include "ImageViewer.h"
#include <QScrollBar>
#include <QDebug>

ImageViewer::ImageViewer(QWidget* parent) : QScrollArea(parent), _imageLabel(new QLabel), _scaleFactor(1.0)
{
    setVisible(false);
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Dark);

    _imageLabel->setBackgroundRole(QPalette::Base);
    _imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _imageLabel->setScaledContents(true);

    setWidget(_imageLabel);
}

ImageViewer::~ImageViewer()
{}

void ImageViewer::setImage(const QImage& img)
{
    _imageLabel->setPixmap(QPixmap::fromImage(img));
    setVisible(true);

    _imageLabel->resize(size().width() - 100, size().height() - 100);

    _scaleFactor = _imageLabel->pixmap()->size().width() / _imageLabel->pixmap()->size().height();

    qDebug() << "SCALE: " << _scaleFactor;
}

void ImageViewer::setImage(const QPixmap& pixmap)
{
    _imageLabel->setPixmap(pixmap);
    setVisible(true);

    _imageLabel->resize(size().width() - 100, size().height() - 100);

    _scaleFactor = _imageLabel->pixmap()->size().width() / _imageLabel->pixmap()->size().height();

    qDebug() << "SCALE: " << _scaleFactor;
}

double ImageViewer::scaleImage(double factor)
{
    _scaleFactor *= factor;
    QSize scaledSize = _scaleFactor * _imageLabel->pixmap()->size();

    qDebug() << "_scaleFactor: " << _scaleFactor;
    qDebug() << "scaledSize: " << scaledSize;

    _imageLabel->resize(scaledSize);

    adjustScrollBar(horizontalScrollBar(), factor);
    adjustScrollBar(verticalScrollBar(), factor);

    return _scaleFactor;
}

void ImageViewer::normalSize()
{
    _imageLabel->adjustSize();
    _scaleFactor = 1.0;
}

void ImageViewer::fitToWindow(bool checked)
{
    setWidgetResizable(checked);

    if (!checked)
    {
        normalSize();
    }
}

void ImageViewer::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep() / 2)));
}
