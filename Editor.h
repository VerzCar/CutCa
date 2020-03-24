#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
#include "ImageViewer.h"
#include "Cutter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

    bool loadFile(const QString &);

private slots:
    void on_actionExit_triggered();

    void on_actionOpenFile_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionFitToWindow_triggered(bool);

    void on_actionNormalSize_triggered();

    void on_actionPrint_triggered();



private:
    Ui::Editor *ui;

    ImageViewer* _imgViewer;
    Cutter* _cutter;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

};
#endif // MAINWINDOW_H
