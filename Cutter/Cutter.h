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
    Cutter(QWidget *parent = nullptr);
    ~Cutter();

private slots:
    void on_btnCapture_clicked();

private:
    Ui::Cutter *ui;
};
#endif // CUTTER_H
