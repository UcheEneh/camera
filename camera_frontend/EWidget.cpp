#include "EWidget.h"
#include "ClipScene.h"

#include <QMouseEvent>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsView>

//USED TO CREATE THE APPLICATION BACKGROUNDS, LABELS ETC
//TRY TO USE THIS TO DRAW THE POINTS
EWidget::EWidget(QWidget* parent) :
    BaseClass(parent)
{
    setAttribute(Qt::WA_StaticContents); //indicates that the widget contents are rooted to the top-left corner and don't change when the widget is resized.
    modified = false;
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::red;

    //create new ui forms/layouts
    m_gridLayout = new QGridLayout(this);               //make app a grid layout form
    m_graphicsView = new QGraphicsView(this);           //create graphics view for showing original image
    m_gridLayout->addWidget(m_graphicsView, 0, 0);      //add grahics view to app

    m_pushButton[0] = new QPushButton("Add file", this);
    m_pushButton[1] = new QPushButton("Save", this);
    m_pushButton[2] = new QPushButton("Close", this);
    m_clippedLabel = new QLabel(this);                  //create label for showing clipped result
    m_clipScene = new ClipScene(this);                  //create instance of included ClipScene to use for clipping

    m_gridLayout->addWidget(m_clippedLabel, 0, 1);      //add clip label to app
    m_gridLayout->addWidget(m_pushButton[0]);//, 1, 0);        //add "add file" pushbutton to app
    m_gridLayout->addWidget(m_pushButton[1]);//, 1, 0);        //add "save" pushbutton to app
    m_gridLayout->addWidget(m_pushButton[2]);//, 1, 0);        //add "close" pushbutton to app

    m_graphicsView->setScene(m_clipScene); //set Graphics View as a clipping region

    connect(m_pushButton[0], &QPushButton::clicked, this, &EWidget::onAddFile);
    connect(m_pushButton[1], &QPushButton::clicked, this, &EWidget::onSaveImage);
    connect(m_pushButton[2], &QPushButton::clicked, this, &EWidget::close);
    connect(m_clipScene, &ClipScene::clippedImage, this, &EWidget::onClippedImage);

    resize(640, 480);
}

void EWidget::onAddFile()
{
    //Crop another image
    QString imagePath = QFileDialog::getOpenFileName(this, "Open Image File", QString(), tr("Image (*.png *.jpg)"));
    m_clipScene->setImage(imagePath);   //opens the image in the graphics view that has been changed to a clipping region

    image = m_clipScene->returnImage();  //get image from clipscene and use
}

void EWidget::onClippedImage(const QPixmap& pixmap)
{
    m_clippedLabel->setPixmap(pixmap);
}

void EWidget::setData(QString &filename) {  //original image is automatically opened in the graphics view that has been changed to a clipping region
    m_clipScene->setImage(filename);
    file = filename;

}

void EWidget::onSaveImage(){

    //############################
    //EDIT FILE PATH TO INCLUDE _cropped
    QString new_file = file;
    QString str2 = ".";
    std::size_t found = new_file.indexOf(str2);
    if (found!=std::string::npos)
        new_file.replace(found, found+3, ""); //str2.length()+3, ""); //delete the .png and replace below

    new_file = new_file + "_cropped.jpg"; //QDir::currentPath() + new_file + "_cropped.png";
    //############################

    //GET IMAGE AND SAVE WITH NEW NAME PATH
    const QPixmap *pic(m_clippedLabel->pixmap());
    QString imagePath = QFileDialog::getSaveFileName(this,tr("Save File"),
                                                     new_file,
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

    //SAVE IMAGE
    QImage *imageObject = new QImage();
    *imageObject = pic->toImage();
    imageObject->save(imagePath);

}


//USE QPAINT TO DRAW POINT
//THESE ARE USELESS HERE, TRY TO PUT IT IN CLIPSCENE.CPP/H INSTEAD

//USE QPAINTER INSTEAD TO ROTATE IMAGE AFTER CROP
void EWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;

        drawPointTo(lastPoint);
    }
}

/*
void EWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}
*/

void EWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        //drawLineTo(event->pos());
        scribbling = false;
    }
}

void EWidget::paintEvent(QPaintEvent *event)   //create a QPainter for the scribble area, and draw the image.
{                                           //i.e. draw in a QImage and copy the QImage onto screen
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void EWidget::resizeEvent(QResizeEvent *event) //when the main window becomes maximized, the image needs to be resized.
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void EWidget::drawPointTo(const QPointF &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(lastPoint);//, endPoint);
    modified = true;

    //int rad = (myPenWidth / 2) + 2;
    update();//QRect(lastPoint, endPoint).normalized()
                                     //.adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}


void EWidget::resizeImage(QImage *image, const QSize &newSize)
{   //create a new QImage with the right size, fill it with white, and draw the old image onto it using QPainter
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
