#ifndef CROPWINDOW_H
#define CROPWINDOW_H

#include <QMainWindow>
#include <QList>

class crop;

class cropwindow : public QMainWindow
{
    Q_OBJECT
public:
    cropwindow();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    crop *Crop;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    //QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // CROPWINDOW_H
