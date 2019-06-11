#include "edit_info.h"
#include "ui_edit_info.h"

#include <QMessageBox>
#include <QDebug>

Edit_Info::Edit_Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_Info)
{
    ui->setupUi(this);
    //make it full screen
    //this->setWindowState(Qt::WindowFullScreen);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();

    if(!connOpen())
        ui->label_Status->setText("Error connecting to database");
    else
        ui->label_Status->setText("Connected to database");

    id = camera.mFilename;
    ui->lineEdit_ID->setText(id);
}

Edit_Info::~Edit_Info()
{
    delete ui;
}

void Edit_Info::on_pushButton_Save_clicked()
{
    //QString id, name, surname, age;
    //id =  ui->lineEdit_ID->text();

    /*
    name = ui->lineEdit_Name->text();
    category =  ui->lineEdit_Category->text();
    date = ui->lineEdit_Date->text();

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("insert into info (id,category,family_name,date) values ('"+id+"', '"+category+"', '"+name+"', '"+date+"')");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Save"), tr("Data is saved"));
        connClose();
    }
    else
        QMessageBox::critical(this,tr("Error::"), qry.lastError().text());
    */

}

void Edit_Info::on_pushButton_Update_clicked()
{
    /*
    id =  ui->lineEdit_ID->text();
    name = ui->lineEdit_Name->text();
    category =  ui->lineEdit_Category->text();
    date = ui->lineEdit_Date->text();

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("update info set id='"+id+"',category= '"+category+"', family_name= '"+name+"', date= '"+date+"' where id= '"+id+"' ");    //eid is set as primary key
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Edit"), tr("Updated"));
        connClose();
    }
    else
        QMessageBox::critical(this,tr("Error::"), qry.lastError().text());
    */
}

void Edit_Info::on_pushButton_Delete_clicked()
{
    /*
    id =  ui->lineEdit_ID->text();
    //name = ui->lineEdit_Name->text();
    //surname =  ui->lineEdit_Surname->text();
    //age = ui->lineEdit_Age->text();

    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("delete from info where id= '"+id+"'");    //we could use name, surname ...
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Delete"), tr("Deleted"));
        connClose();
    }
    else
         QMessageBox::critical(this,tr("Error::"), qry.lastError().text());
    */
}

void Edit_Info::on_pushButton_View_clicked()
{
    /*
    id = ui->lineEdit_ID->text();
    if(!connOpen())
    {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("select category,family_name,date from info where id ='"+id+"'");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("View"), tr("View data"));
        connClose();
    }
    else
        QMessageBox::critical(this,tr("Error::"), qry.lastError().text());

    category = ;
    name = ;
    date = ;
    ui->lineEdit_Category->setText(category);
    ui->lineEdit_Name->setText(name);
    ui->lineEdit_Date->setText(date);
    */

}

void Edit_Info::on_pushButton_Back_clicked()
{
    close();
}
