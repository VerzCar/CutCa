#ifndef CUTSELECTOR_H
#define CUTSELECTOR_H

#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QMouseEvent>

class CutSelector : public QDialog
{
    Q_OBJECT
  public:
    explicit CutSelector(QWidget* parent = nullptr);

    QPixmap grabScreenshot();

    const QPixmap& getCroppedSelection();

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;


  public slots:

  private:
    QPixmap _desktopPixmap;
    QRect _selectedRect;
    QPixmap _selectedPixmap;
};

#endif // CUTSELECTOR_H
