#include "edit_info.h"
#include "ui_edit_info.h"

//#include "cropwindow.h"


#include <QtWidgets>
#include <QFile>
#include <QDebug>
#include <QTimer>

#include <QMouseEvent>

edit_info::edit_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_info)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::Window);     //better for android
    //this->showFullScreen();

    if(!connOpen())
        ui->label_Status->setText("Disconnected from Database");
    else
        ui->label_Status->setText("Connected to Database");

    m_clipScene = new ClipScene(this);
    ui->m_graphicsView->setScene(m_clipScene); //set Graphics View as a clipping region

    /*
    connect(ui->m_pushButton_Add, &QPushButton::clicked, this, &edit_info::onAddFile);
    connect(ui->m_pushButton_Save, &QPushButton::clicked, this, &edit_info::onSaveImage);
    connect(m_clipScene, &ClipScene::clippedImage, this, &edit_info::onClippedImage);
    //everytime a box is selected and the mouse is released, clippedImage signal is activated
    //which copies the image in the selected box/region onto the clipLabel here

    connect(ui->pushButton_Undo, &QPushButton::clicked, this, &edit_info::undoCrop);
    connect(ui->pushButton_deletePoints, &QPushButton::clicked, this, &edit_info::deletePoints);
    */
    connect(ui->pushButton_Back, &QPushButton::clicked, this, &edit_info::close);
    connect(ui->pushButton_Load, &QPushButton::clicked, this, &edit_info::loadTable);

    //connect(ui->pushButton_deletePoints_2, &QPushButton::clicked, this, &edit_info::deletePoints2);

}

edit_info::~edit_info()
{
    delete ui;
}

//-------------------------------------- DATABASE CREATION --------------------------------------//
bool edit_info::connOpen()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    /*
    db.setHostName("74.208.235.215");  //("vpn.eid.im");
    db.setDatabaseName("uche_test_db");
    db.setPort(3306);
    db.setUserName("uche_test_dba");
    db.setPassword("*T4rk8e9");
    */

    db.setHostName("sql202.epizy.com");
    db.setDatabaseName("epiz_23054611_info2");
    db.setPort(3306);
    db.setUserName("epiz_23054611");
    db.setPassword("XHjlNpoRPAtDHyY");

    if(!db.open())
    {
        QMessageBox::warning(this, tr("Failed to connect!"), tr("Error connecting to database: ")+db.lastError().driverText() );
        return false;
    }
    return true;
}

void edit_info::connClose()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}
//------------------------------------------------------------------------------------------------//







//---------------------------- SET DATA FROM CAMERA ----------------------------------------------//
//##########################################################
//To display the transferred data (filename) from camera.cpp
void edit_info::setData(QString &filename) {
    ui->lineEdit_ImageName->setText(filename);

    //automatically open original image in graphics view (that has been changed to a clipping region)
    if (ui->lineEdit_ImageName->text().isEmpty())
        return;
    else
    {
        m_clipScene->setImage(ui->lineEdit_ImageName->text());
        file = ui->lineEdit_ImageName->text();
    }
}
//------------------------------------------------------------------------------------------------//






//----------------------------------- EDIT TABLE IN DATABASE --------------------------------------//
//#################################     INFO     #################################
void edit_info::on_pushButton_Save_clicked()
{
    QString name, category, date, imagePath;
    QByteArray image;
    //int id;

    //id = ui->lineEdit_ID->text().toInt();
    category =  ui->lineEdit_Category->text();
    name = ui->lineEdit_Name->text();
    date = ui->lineEdit_Date->text();
    imagePath = ui->lineEdit_ImageName->text();

    //**************** SAVE IMAGE AS BLOB ****************//
    //BLOB format is also suitable for storing images, audio and video data in databases.
    //BLOB (Binary Large Object) is an array of binary data format.

    //Save the image as ByteArray
    QPixmap inPixmap(imagePath);                       // Save image as QPixmap
    QByteArray inByteArray;                        // Create QByteArray object to save the image
    QBuffer inBuffer( &inByteArray );              // Saving images produced through the buffer
    inBuffer.open( QIODevice::WriteOnly );         // Open buffer
    inPixmap.save( &inBuffer, "PNG" );             // Write inPixmap in inByteArray

    //Store image for use in table
    image = inByteArray;
    //****************************************************//

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry = QSqlQuery(db);   //this would make the query run from the database******

    //REMOVED imagepath FROM DATABASE, AND NOW id INCREMENTS AUTOMATICALLY

    //qry.prepare("insert into info2 (id,category,name,date,image) values (?,?,?,?,?,?)");
    qry.prepare("insert into info2 (category,name,date,image) values (?,?,?,?)");
    //qry.addBindValue(id);
    qry.addBindValue(category);
    qry.addBindValue(name);
    qry.addBindValue(date);
    //qry.addBindValue(imagePath);
    qry.addBindValue(image);     //to show picture

    if(qry.exec())
    {
        //QMessageBox::critical(this,tr("Save"), tr("Data is saved"));
        ui->label_query->setText("Saved");
        connClose();
    }
    else
        QMessageBox::critical(this,tr("Error::"), qry.lastError().text());

    if(loadClicked)
        loadTable();
}

void edit_info::on_pushButton_Update_clicked()
{
    QString name, category, date, imagePath;
    QByteArray image;
    //int id;

    //id = ui->lineEdit_ID->text().toInt();
    category =  ui->lineEdit_Category->text();
    name = ui->lineEdit_Name->text();
    date = ui->lineEdit_Date->text();
    imagePath = ui->lineEdit_ImageName->text();

    //**************** UPDATE IMAGE AS BLOB ****************//
    //Save the image as ByteArray
    QPixmap inPixmap(imagePath);                       // Save image as QPixmap
    QByteArray inByteArray;                        // Create QByteArray object to save the image
    QBuffer inBuffer( &inByteArray );              // Saving images produced through the buffer
    inBuffer.open( QIODevice::WriteOnly );         // Open buffer
    inPixmap.save( &inBuffer, "PNG" );             // Write inPixmap in inByteArray

    //Store image for use in table
    image = inByteArray;
    //******************************************************//

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry = QSqlQuery(db);   //this would make the query run from the database******
    //qry.prepare("update info2 set id=:id ,category= :category, name= :name, date= :date, image= :image where id= :id");    //id is set as primary key
    qry.prepare("update info2 set category= :category, name= :name, date= :date, image= :image where name= :name");    //id is set as primary key
    //qry.bindValue(":id", id);
    qry.bindValue(":category", category);
    qry.bindValue(":name", name);
    qry.bindValue(":date", date);
    //qry.bindValue(":image", imagePath);
    qry.bindValue(":image", image);

    //Warning after update has been clicked
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("camera"),
                                 tr("The table has been updated.\n" "Do you want to save your changes?"),
                                 QMessageBox::Save | QMessageBox::Cancel,
                                 QMessageBox::Save);

    if (reply == QMessageBox::Save)
    {
        if(qry.exec())
        {
            //QMessageBox::critical(this,tr("Edit"), tr("Updated"));
            ui->label_query->setText("Updated");
            connClose();
        }
        else
            QMessageBox::critical(this,tr("Error::"), qry.lastError().text());

        if(loadClicked)
            loadTable();;
    }

}

void edit_info::on_pushButton_Delete_clicked()
{
    QString name;
    //QString category, date;
    //QByteArray tablepic;
    //int id;

    //id = ui->lineEdit_ID->text().toInt();
    //category =  ui->lineEdit_Category->text();
    name = ui->lineEdit_Name->text();
    //date = ui->lineEdit_Date->text();

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry = QSqlQuery(db);
    qry.prepare("delete from info2 where name= :name");    //we could use id, category ...
    qry.bindValue(":name", name);

    //Warning after delete has been clicked
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("camera"),
                                 tr("Are you sure you want to delete this from the table?"),
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        if(qry.exec())
        {
            //QMessageBox::critical(this,tr("Delete"), tr("Deleted"));
            ui->label_query->setText("Deleted");
            connClose();
        }
        else
             QMessageBox::critical(this,tr("Error::"), qry.lastError().text());

        if(loadClicked)
            loadTable();
    }
}


//Load the database in a table format
void edit_info::loadTable()
{
    connOpen();

    model = new QSqlQueryModel(this);
    model->setQuery("select * from info2");
    ui->tableView->setModel(model);    //set table

    //Configure table
    //ui->tableView->setColumnHidden(0, true);    //hide col id
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //allow selection of lines
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //set selection mode only one row in table
    ui->tableView->resizeColumnsToContents();   //set size of cols by content
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //Connect the signal currentRowChanged in the table to the slot method that displays the
    //selcted row's image in pic_table Label and other details in their respective lineEdits
    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(slotCurrentPic(QModelIndex)));

    loadClicked = true;
    //connClose();
}

void edit_info::slotCurrentPic(QModelIndex index)
{
    QPixmap outPixmap = QPixmap(); // Create QPixmap, which will be placed in picLabel

    //------- Taking the image data from the table as QByteArray and put them in QPixmap -------//
    //Basically, use the information in the col. 5 position of the currently selected index/row
    //in the table to load the image
    outPixmap.loadFromData(model->data(model->index(index.row(), 4)).toByteArray()); //index 4 because we count from 0 - 4, not 1 - 5
    outPixmap = outPixmap.scaledToWidth(ui->label_pic_table->width(), Qt::SmoothTransformation); //Scale to width
    ui->label_pic_table->setPixmap(outPixmap);

    //EXTRA: also set other details in lineedit to be displayed when row selected
    ui->lineEdit_ID->setText(model->data(model->index(index.row(), 0)).toString());
    ui->lineEdit_Category->setText(model->data(model->index(index.row(), 1)).toString());
    ui->lineEdit_Name->setText(model->data(model->index(index.row(), 2)).toString());
    ui->lineEdit_Date->setText(model->data(model->index(index.row(), 3)).toString());
    //ui->lineEdit_ImageName->setText(model->data(model->index(index.row(), 4)).toString());
}
//------------------------------------------------------------------------------------------------//







//------------------------------- OPEN/SHOW IMAGES IN LABELS ------------------------------------//

void edit_info::on_pushButton_showImage_clicked()
{
    QString imagename;
    imagename = ui->lineEdit_ImageName->text();

    if (!imagename.isEmpty())   //if a picture has been taken
    {
        QImage img(imagename);
        img = img.scaledToWidth(ui->label_showImage->width(), Qt::SmoothTransformation);
        ui->label_showImage->setPixmap(QPixmap::fromImage(img));
    }

    else    //else, ask to open from folder
    {
        //Warning if show image clicked and no image selected
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("camera"),
                                     tr("No image has been selected. \n"
                                        "Do you want to load an image from a folder?"),
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);
        if (reply == QMessageBox::Yes)
        {
            on_pushButton_openImage_clicked();
        }
     }

    //Another way to scale image and show
    //ui->label_showImage->setPixmap(QPixmap::fromImage(img).scaled(QSize(ui->label_showImage->width(),
                                                                        //ui->label_showImage->height()),
                                                           //Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void edit_info::on_pushButton_openImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Open Image File", QString(), tr("Image (*.png *.jpg)"));
    QImage img(imagePath);
    img = img.scaledToWidth(ui->label_showImage->width(), Qt::SmoothTransformation);
    ui->label_showImage->setPixmap(QPixmap::fromImage(img));
    ui->lineEdit_ImageName->setText(imagePath); //set line edit to be the new image path

}


//------------------------------------------------------------------------------------------------//





//----------------- OPENCV CROP WITH NEW DIALOG (NOT IMPLEMENTED)---------------------------------//
/*
void edit_info::mousePressEvent(QMouseEvent *event)
{
    //TODO: if mouse is on the qlabel then:
    if(event->button() == Qt::LeftButton)
    {
        leftMouseButtonPressed = true;
        if (ui->label_showImage->isEnabled())   //check if .isEnabled is the proper term
        {
            pressCount_cv++;

            if(pointsVector_cv.count() < 4)
            {
                auto x(event->pos().x());     //change these to be better
                auto y(event->pos().y());
                cv::Point2f point_xy_cv(x, y);
                pointsVector_cv.append(point_xy_cv);
            }
        }
    }
}

void edit_info::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftMouseButtonPressed = false;

        if(pressCount_cv == 4)
        {
            //------------------ METHOD OPENCV ------------------------------------//
            QString name = ui->lineEdit_ImageName->text();
            std::string filepath = name.toUtf8().constData();
            cv::Mat source_image = cv::imread(filepath);

            //And you have four points you want to use as the corners:
            cv::Point corners[1][4];
            corners[0][0] = pointsVector_cv[0];    //cv::Point2f(30, 30);    //point 1
            corners[0][1] = pointsVector_cv[1];    //cv::Point2f(100, 100);    //point 2
            corners[0][2] = pointsVector_cv[2];    //cv::Point2f(200, 50);    //point 3
            corners[0][3] = pointsVector_cv[3];    //cv::Point2f(50, 25);     //point 4
            const cv::Point* corner_list[1] = {corners[0]};

            //You can use the function cv::fillPoly to draw this shape on a mask:
            int num_points = 4;
            int num_polygons = 1;
            int line_type = 8;
            cv::Mat mask(source_image.rows, source_image.cols, CV_8UC3, cv::Scalar(0,0,0));
            cv::fillPoly(mask, corner_list, &num_points, num_polygons, cv::Scalar(255, 255, 255), line_type);

            //Then simply compute the bitwise_and of the image and mask:
            cv::Mat result;
            cv::bitwise_and(source_image, mask, result);    //result now has the cropped image in it

            //cv::namedWindow("cropped image", cv::WINDOW_FREERATIO);
            //cv::imshow("cropped image", result);
            //cv::waitKey(0);
        }
    }
}

void edit_info::deletePoints2()
{
    pressCount_cv = 0;
    pointsVector_cv.clear();
}
*/
void edit_info::on_pushButton_Crop_clicked()
{
    //this->close();
}



//----------------------------------- ROTATE IMAGE ---------------------------------------------//
//ERROR: IMAGE GETS AFFECTED/SMALLER DUIRNG ROTATION
//USE OTHER METHODS WITH BETTER TRANSFORMATION
void edit_info::on_pushButton_Rotate_clicked()
{
    QPixmap rotatedPic(*ui->label_showImage->pixmap());
    QMatrix rm;

    int angle = ui->lineEdit_rotateAngle->text().toInt();
    rm.rotate(angle);
    rotatedPic = rotatedPic.transformed(rm).scaled(ui->label_showImage->width(),
                                                   ui->label_showImage->height(),
                                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_showImage->setPixmap(rotatedPic);
}




//-------------------------------- CROPPING / CLIP SCENE ----------------------------------------//
/*
void edit_info::onAddFile()
{
    //Crop another image
    QString imagePath = QFileDialog::getOpenFileName(this, "Open Image File", QString(), tr("Image (*.png *.jpg)"));
    m_clipScene->setImage(imagePath);   //opens the image in the graphics view that has been changed to a clipping region

    image = m_clipScene->returnImage();  //get image from clipscene and use for QPaint (REMOVED)!!!!

    file = imagePath;   //set file as image path to be used later for naming the cropped image
}

void edit_info::onClippedImage(const QPixmap& pixmap)
{
    ui->m_clippedLabel->setPixmap(pixmap);
}


void edit_info::onSaveImage(){

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
    const QPixmap *pic(ui->m_clippedLabel->pixmap());
    QString imagePath = QFileDialog::getSaveFileName(this,tr("Save File"),
                                                     new_file,
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    //SAVE IMAGE
    QImage *imageObject = new QImage();
    *imageObject = pic->toImage();

    if(imageObject->save(imagePath))    //if image is saved:
    {
        cropPerformed = true;

        //clear graphicsview and load cropped image onto it
        m_clipScene->setImage(imagePath);

        //and change imagepath in lineEdit_ImageName
        ui->lineEdit_ImageName->setText(imagePath);

        //if this can be done, move original image to another folder!!!!!!!!!!!!!!!
    }

}

void edit_info::undoCrop()  //Just basic replotting, nothing hardcore here
{

    if(cropPerformed)   //after save is clicked, cropPerformed = true
    {
        //m_clipScene->undoPoints();  //maybe leave this here as well

        //Warning if undo clicked
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("Undo"),
                                     tr("Revert back to original image? \n"),
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::Yes);
        if (reply == QMessageBox::Yes)
        {
            //clear graphicsview and reload original image
            m_clipScene->setImage(file);

            //and change back imagepath in lineEdit_ImageName
            ui->lineEdit_ImageName->setText(file);
        }

    }

    else
    {
        QMessageBox::warning(this, tr("Undo"),
                             tr("No changes have been made to an image"),
                             QMessageBox::Close);
    }

    cropPerformed = false;
}

void edit_info::deletePoints()  //Just basic replotting, nothing hardcore here
{
    if(m_clipScene->polygonAdded)   //specific for polygon added
        m_clipScene->undoPoints();
}
*/
//------------------------------------------------------------------------------------------------//

