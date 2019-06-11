#include "crop_dialog.h"
#include "ui_cropdialog.h"


#include <QtWidgets>
#include <QFile>
#include <QDebug>
#include <QTimer>

#include <QMouseEvent>

crop_dialog::crop_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crop_dialog)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::Window);     //better for android
    //this->showFullScreen();

    //CREATE DB CONNECTION HERE

    m_clipScene = new ClipScene(this);



}

crop_dialog::~crop_dialog()
{
    delete ui;
}
