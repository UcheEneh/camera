#ifndef EDIT_INFO_H
#define EDIT_INFO_H

#include <QDialog>

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>

#include "camera.h"

namespace Ui {
class Edit_Info;
}

class Edit_Info : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_Info(QWidget *parent = 0);
    ~Edit_Info();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //open db connection
    bool connOpen()
    {
        db.setDatabaseName("hierog.db");
        if(!db.open())
        {
            QMessageBox::warning(this, tr("Failed to connect!"), tr("Error connecting to database: ")+db.lastError().driverText() );
            return false;
        }
        return true;
    }

    //close db and removing default connection
    void connClose()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    QString id, name, category, date;
    Camera camera;


private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_View_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::Edit_Info *ui;
};

#endif // EDIT_INFO_H
