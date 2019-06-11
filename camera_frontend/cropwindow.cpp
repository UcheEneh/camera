#include <QtWidgets>

#include "cropwindow.h"
#include "crop.h"

cropwindow::cropwindow()
{
    Crop = new crop;
    setCentralWidget(Crop);

    createActions();
    createMenus();

    setWindowTitle(tr("Crop"));
    resize(500, 500);
}

void cropwindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {      //If true, there are no modifications or the users successfully saved them,
        event->accept();    //and we accept the event. The application can then terminate normally.
    } else {
        event->ignore();    //If false, the user clicked Cancel, so we "ignore" the event,
    }                       //leaving the application unaffected by it.
}

void cropwindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            /*
            QImage img(fileName);
            img = img.scaledToWidth(ui->label_showImage->width(), Qt::SmoothTransformation);
            ui->label_showImage->setPixmap(QPixmap::fromImage(img));
            */
            Crop->openImage(fileName); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
}

void cropwindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender()); //find out which action sent the signal using QObject::sender()
    QByteArray fileFormat = action->data().toByteArray(); //we extract the chosen format using QAction::data()
    saveFile(fileFormat); //now that we know the format, call saveFile() to save currently displayed image.
}

void cropwindow::penColor()
{
    QColor newColor = QColorDialog::getColor(Crop->penColor());
    if (newColor.isValid())
        Crop->setPenColor(newColor);
}

void cropwindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        Crop->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        Crop->setPenWidth(newWidth);
}

void cropwindow::about()
{
    QMessageBox::about(this, tr("About Hiero"),
            tr("<p>The <b>Hiero</b> example shows how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}

void cropwindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);  //implements shortcut
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    //create the actions found in the Save As sub-menu for all supported formats
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format); //used so we can retrieve the format later using QAction::data().
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    //printAct = new QAction(tr("&Print..."), this);
    //connect(printAct, SIGNAL(triggered()), Crop, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            Crop, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void cropwindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    //fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool cropwindow::maybeSave()
{
    if (Crop->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool cropwindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return Crop->saveImage(fileName, fileFormat.constData());
    }
}
