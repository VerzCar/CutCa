#ifndef CUTTER_H
#define CUTTER_H

#include <QDialog>

namespace Ui {
class Cutter;
}

class Cutter : public QDialog
{
    Q_OBJECT

public:
    explicit Cutter(QWidget *parent = nullptr);
    ~Cutter();

private slots:
    void on_btnCapture_clicked();

private:
    Ui::Cutter *ui;
};

#endif // CUTTER_H
