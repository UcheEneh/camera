#ifndef EDIT_INFO_H
#define EDIT_INFO_H

#include <QDialog>

//#include <QMainWindow>
//#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QModelIndex>

//OPENCV, IF ADDED HERE, THEN SHOULD BE DELETED FROM CLIPSCENE.H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//#include "EWidget.h"

#include "ClipScene.h"

namespace Ui {
class edit_info;
}

//class ClipScene;

class edit_info : public QDialog
{
    Q_OBJECT

public:
    explicit edit_info(QWidget *parent = nullptr);

    //edit_info(QWidget *parent = 0, bool);

    ~edit_info();

    QString imagename;
    QSqlDatabase db;
    bool loadClicked = false;   //would be used to tell if load button has been clicked initially
    void setData (QString &filename);
    void connClose();
    bool connOpen();
    void loadTable();   //load table from database

//protected:
    //void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    //void paintEvent(QPaintEvent *event) override;
    //void resizeEvent(QResizeEvent *event) override;

private slots:
    //Edit Info
    void on_pushButton_Save_clicked();
    void on_pushButton_Update_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_showImage_clicked();
    void on_pushButton_openImage_clicked();

    void slotCurrentPic(QModelIndex index);

    void on_pushButton_Crop_clicked();
    void on_pushButton_Rotate_clicked();

    //CROP FUNCTIONALITIES
    /*
    void onAddFile();                           // Slot for adding an image to the application
    void onClippedImage(const QPixmap& pixmap); // Slot for accepting a cropped application area
    void onSaveImage();                         // Slot for saving cropped image (For now, also closes)
    void undoCrop();                            //Slot for reloading original image
    void deletePoints();                        //Slot to delete polygon points

    void deletePoints2();                       //Slot for deleting points on OPENCV
    */
private:
    Ui::edit_info *ui;
    QSqlQueryModel *model;


    ClipScene* m_clipScene;         // The graphical scene in which the image trimming functionality is implemented

    //USE QPAINTER INSTEAD TO SELECT POINTS FOR CROPPING IMAGE/ROTATE IMAGE AFTER CROP
    //void drawPointTo(const QPointF &endPoint);
    //void resizeImage(QImage *image, const QSize &newSize);


    QImage image;
    QPointF lastPoint;

    QString file;

    /*
    bool cropPerformed = false;
    bool leftMouseButtonPressed           {false};

    //WITH OPENCV
    QVector<cv::Point2f> pointsVector_cv;
    int pressCount_cv = 0;
    */
};

#endif // EDIT_INFO_H
