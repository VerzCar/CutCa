#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool loadFile(const QString &);

private slots:
        void on_actionExit_triggered();

    void on_actionOpenFile_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();



private:
    Ui::MainWindow *ui;

    double _scaleFactor = 1;

    void scaleImage(double factor);

    void normalSize();

    void fitToWindow();

    void adjustScrollBar(QScrollBar *scrollBar, double factor);

};
#endif // MAINWINDOW_H
