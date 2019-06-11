#pragma once

#include <QtWidgets/QWidget>

#include "edit_info.h"

class QGridLayout;
class QPushButton;
class QGraphicsView;
class QLabel;
class ClipScene;

//USE QDIALOG FOR THIS INSTEAD
class EWidget : public QWidget
{
    using BaseClass = QWidget;

    Q_OBJECT

public:
    EWidget(QWidget* parent = nullptr);
    void setData (QString &filename);   //for opening the original image
    bool closed;        //trying to use this to reopen hidden edit_info window

protected:  //added for drawing points
    void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onAddFile();                           // Slot for adding an image to the application
    void onClippedImage(const QPixmap& pixmap); // Slot for accepting a cropped application area
    void onSaveImage();                         // Slot for saving cropped image (For now, also closes)

private:
    QGridLayout* m_gridLayout;
    QPushButton* m_pushButton[3];
    QGraphicsView* m_graphicsView;
    QLabel* m_clippedLabel;         // A label in which the cropped image will be placed
    ClipScene* m_clipScene;         // The graphical scene in which the image trimming functionality is implemented

    //added for drawing points
    //MAYBE MORE USEFUL IN CLIPSCENE.CPP/H

    //USE QPAINTER INSTEAD TO ROTATE IMAGE AFTER CROP
    void drawPointTo(const QPointF &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPointF lastPoint;

    QString file;
};

