#ifndef CUTTER_H
#define CUTTER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Cutter; }
QT_END_NAMESPACE


class Cutter : public QDialog
{
    Q_OBJECT

  public:
    Cutter(QWidget* parent = nullptr);
    ~Cutter();

    //!
    //! \brief hasCroppedPixmap determine if the cutter currently
    //! contains a cropped pixmap.
    //! \return true if it contains a cropped pixmap, otherwise false.
    //!
    bool hasCroppedPixmap();

    //!
    //! \brief getCroppedPixmap gets the current cropped pixmap.
    //! \return current cropped pixmap.
    //!
    const QPixmap* getCroppedPixmap();

  signals:
    void cutted();

  private slots:
    void on_btnCapture_clicked();

  private:
    Ui::Cutter* ui;

    QPixmap _currentCroppedSelection;
};

#endif // CUTTER_H
