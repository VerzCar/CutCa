#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QScrollArea>
#include <QMouseEvent>
#include <QLabel>

class ImageViewer : public QScrollArea
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget* parent = nullptr);

    ~ImageViewer();

    void setImage(const QImage& img);

    double scaleImage(double factor);

    void  normalSize();

    void fitToWindow(bool checked);

private:
    QLabel* _imageLabel;
    double _scaleFactor;

    void adjustScrollBar(QScrollBar *scrollBar, double factor);

};

#endif // IMAGEVIEWER_H
