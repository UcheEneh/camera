//ScribbleArea, where the crop functions are made

#include <QtWidgets>
/*
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
*/
#include "crop.h"

crop::crop(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents); //indicates that the widget contents are rooted to the top-left corner and don't change when the widget is resized.
    modified = false;
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::blue;
}

bool crop::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName)) // we load the given image.
        return false;

    QSize newSize = loadedImage.size().expandedTo(size()); //size() returns the size of the widget
    resizeImage(&loadedImage, newSize); //we resize the loaded QImage to be at least as large as the widget in both directions
    image = loadedImage;
    modified = false;
    update(); //we call QWidget::update() to schedule a repaint.
    return true;
}

bool crop::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void crop::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void crop::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void crop::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void crop::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;

        drawPointTo(lastPoint);
    }
}

/*
void crop::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}
*/

void crop::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        //drawLineTo(event->pos());
        scribbling = false;
    }
}

void crop::paintEvent(QPaintEvent *event)   //create a QPainter for the scribble area, and draw the image.
{                                           //i.e. draw in a QImage and copy the QImage onto screen
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void crop::resizeEvent(QResizeEvent *event) //when the main window becomes maximized, the image needs to be resized.
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void crop::drawPointTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(lastPoint);//, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void crop::resizeImage(QImage *image, const QSize &newSize)
{   //create a new QImage with the right size, fill it with white, and draw the old image onto it using QPainter
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

//########################## PRINT ########################
/*
void crop::print()
{
#if QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
//! [21] //! [22]
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
*/
