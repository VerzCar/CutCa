#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QScreen>
#include <QStandardPaths>
#include <QImageWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), imageLabel(new QLabel)
{
    ui->setupUi(this);

    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);

    ui->ImageViewerScrollArea->setBackgroundRole(QPalette::Dark);
    //ui->ImageViewerScrollArea->setWidget(ui->imageLabel);
    ui->ImageViewerScrollArea->setVisible(true);
    //setCentralWidget(ui->ImageViewerScrollArea);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();

    for (const QByteArray &mimeTypeName : supportedMimeTypes)
    {
        mimeTypeFilters.append(mimeTypeName);
    }

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    if (acceptMode == QFileDialog::AcceptSave)
    {
        dialog.setDefaultSuffix("jpg");
    }
}

void MainWindow::on_actionOpenFile_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2").arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    _scaleFactor = 1.0;

  ui->imageLabel->setPixmap(QPixmap::fromImage(newImage));
    //ui->imageLabel->adjustSize();

    return true;
//    scrollArea->setVisible(true);
//    printAct->setEnabled(true);
//    fitToWindowAct->setEnabled(true);
//    updateActions();

//    if (!fitToWindowAct->isChecked())
//        imageLabel->adjustSize();
}

void MainWindow::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
}

void MainWindow::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(ui->imageLabel->pixmap());

    _scaleFactor *= factor;
    ui->imageLabel->resize(_scaleFactor * ui->imageLabel->pixmap()->size());

    adjustScrollBar(ui->ImageViewerScrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->ImageViewerScrollArea->verticalScrollBar(), factor);

   ui->actionZoomIn->setEnabled(_scaleFactor < 3.0);
ui->actionZoomOut->setEnabled(_scaleFactor > 0.333);
}

void MainWindow::normalSize()
{
    ui->imageLabel->adjustSize();
    _scaleFactor = 1.0;
}

void MainWindow::fitToWindow()
{
//    bool fitToWindow = fitToWindowAct->isChecked();
//    scrollArea->setWidgetResizable(fitToWindow);
//    if (!fitToWindow)
//        normalSize();
//    updateActions();
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

