#ifndef CROP_DIALOG_H
#define CROP_DIALOG_H

#include <QDialog>

#include <QFileInfo>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "ClipScene.h"

namespace Ui {
class crop_dialog;
}

class ClipScene;

class crop_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit crop_dialog(QWidget *parent = nullptr);
    ~crop_dialog();

    void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onAddFile();                           // Slot for adding an image to the application
    void onClippedImage(const QPixmap& pixmap); // Slot for accepting a cropped application area
    void onSaveImage();                         // Slot for saving cropped image (For now, also closes)
    void undoCrop();                            //Slot for reloading original image
    void deletePoints();                        //Slot to delete polygon points
    void deletePoints2();                       //Slot for deleting points on OPENCV


private:
    Ui::crop_dialog *ui;

    ClipScene* m_clipScene;         // The graphical scene in which the image trimming functionality is implemented

    QImage image;
    QPointF lastPoint;

    QString file;

    bool cropPerformed = false;
    bool leftMouseButtonPressed           {false};

    //WITH OPENCV
    QVector<cv::Point2f> pointsVector_cv;
    int pressCount_cv = 0;

};

#endif // CROP_DIALOG_H
