#ifndef CUTSELECTOR_H
#define CUTSELECTOR_H

#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>

class CutSelector : public QDialog
{
    Q_OBJECT
  public:
    explicit CutSelector(QWidget* parent = nullptr);
    ~CutSelector();

    QPixmap grabScreenshot();

    const QPixmap& getCroppedSelection();

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;


  public slots:

  private:
    QPixmap _desktopPixmap;
    QImage _desktopImage;
    QRect _selectedRect;
    QPixmap _selectedPixmap;
    bool _isMouseClicked;
};

#endif // CUTSELECTOR_H
