#include "Editor.h"
#include "ui_Editor.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QScreen>
#include <QStandardPaths>
#include <QImageWriter>
#include <QPrintDialog>
#include <QPainter>

Editor::Editor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor),
      _imgViewer(new ImageViewer),
      _cutter(new Cutter)
{
    ui->setupUi(this);

    ui->imageViewerLayout->addWidget(_imgViewer);

    ui->actionFitToWindow->setEnabled(false);
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);
    ui->actionZoomOut->setEnabled(false);
    ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);
    ui->actionPrint->setShortcut(QKeySequence::Print);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    connect(_cutter, SIGNAL(cutted()), this, SLOT(setCuttedPixmap()));
    _cutter->show();

}

Editor::~Editor()
{
    delete ui;
    delete _imgViewer;
    delete _cutter;
}

void Editor::on_actionExit_triggered()
{
    close();
}

static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen ? QImageReader::supportedMimeTypes() :
                                              QImageWriter::supportedMimeTypes();

    for (const QByteArray& mimeTypeName : supportedMimeTypes)
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

void Editor::on_actionOpenFile_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool Editor::loadFile(const QString& fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    if (newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2").arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    _imgViewer->setImage(newImage);

    ui->actionFitToWindow->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);

    return true;
}


void Editor::on_actionZoomIn_triggered()
{
    double factor = _imgViewer->scaleImage(1.25);

    ui->actionZoomIn->setEnabled(factor < 3.0);
    ui->actionZoomOut->setEnabled(factor > 0.333);
}

void Editor::on_actionZoomOut_triggered()
{
    double factor = _imgViewer->scaleImage(0.8);

    ui->actionZoomIn->setEnabled(factor < 3.0);
    ui->actionZoomOut->setEnabled(factor > 0.15);
}

void Editor::on_actionFitToWindow_triggered(bool checked)
{
    _imgViewer->fitToWindow(checked);

    if (checked)
    {
        ui->actionZoomIn->setEnabled(false);
        ui->actionZoomOut->setEnabled(false);
    }
    else
    {
        ui->actionZoomIn->setEnabled(true);
        ui->actionZoomOut->setEnabled(true);
    }
}

void Editor::on_actionNormalSize_triggered()
{
    _imgViewer->normalSize();
}


void Editor::on_actionPrint_triggered()
{
    //    Q_ASSERT(_imageLabel->pixmap());
    //#if QT_CONFIG(printdialog)
    //    if (!_imageLabel->pixmap())
    //        qFatal("ASSERT: ", _imageLabel->pixmap(), " in file ...");
    //    QPrintDialog dialog(&printer, this);
    //    if (dialog.exec()) {
    //        QPainter painter(&printer);
    //        QRect rect = painter.viewport();
    //        QSize size = _imageLabel->pixmap()->size();
    //        size.scale(rect.size(), Qt::KeepAspectRatio);
    //        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    //        painter.setWindow(_imageLabel->pixmap()->rect());
    //        painter.drawPixmap(0, 0, *_imageLabel->pixmap());
    //    }
    //#endif
}

void Editor::setCuttedPixmap()
{
    _imgViewer->setImage(*_cutter->getCroppedPixmap());

    ui->actionFitToWindow->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
}
