/********************************************************************************
** Form generated from reading UI file 'edit_info.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_INFO_H
#define UI_EDIT_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_edit_info
{
public:
    QLabel *label_showImage;
    QLabel *label_Status;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_ImageName;
    QLabel *label_Category;
    QLabel *label_Name;
    QLabel *label_Image;
    QLineEdit *lineEdit_ID;
    QLineEdit *lineEdit_Category;
    QLabel *label_ID;
    QLineEdit *lineEdit_Date;
    QLineEdit *lineEdit_Name;
    QLabel *label_Date;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_Delete;
    QPushButton *pushButton_Back;
    QPushButton *pushButton_Load;
    QPushButton *pushButton_Update;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Save;
    QTableView *tableView;
    QLabel *label_query;
    QLabel *label_pic_table;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Rotate;
    QLineEdit *lineEdit_rotateAngle;
    QWidget *gridLayoutWidget;
    QGridLayout *m_gridLayout;
    QGraphicsView *m_graphicsView;
    QLabel *m_clippedLabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_showImage;
    QPushButton *pushButton_openImage;
    QPushButton *pushButton_Crop;
    QPushButton *pushButton_deletePoints;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_pushButton_Add;
    QPushButton *m_pushButton_Save;
    QPushButton *pushButton_Undo;
    QPushButton *pushButton_deletePoints_2;

    void setupUi(QDialog *edit_info)
    {
        if (edit_info->objectName().isEmpty())
            edit_info->setObjectName(QStringLiteral("edit_info"));
        edit_info->resize(1245, 877);
        label_showImage = new QLabel(edit_info);
        label_showImage->setObjectName(QStringLiteral("label_showImage"));
        label_showImage->setGeometry(QRect(220, 100, 271, 191));
        label_showImage->setMouseTracking(true);
        label_showImage->setTabletTracking(true);
        label_showImage->setFrameShape(QFrame::Box);
        label_Status = new QLabel(edit_info);
        label_Status->setObjectName(QStringLiteral("label_Status"));
        label_Status->setGeometry(QRect(10, 440, 161, 31));
        groupBox = new QGroupBox(edit_info);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 211, 361));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 21, 191, 339));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_ImageName = new QLineEdit(layoutWidget);
        lineEdit_ImageName->setObjectName(QStringLiteral("lineEdit_ImageName"));

        gridLayout->addWidget(lineEdit_ImageName, 4, 1, 1, 1);

        label_Category = new QLabel(layoutWidget);
        label_Category->setObjectName(QStringLiteral("label_Category"));

        gridLayout->addWidget(label_Category, 1, 0, 1, 1);

        label_Name = new QLabel(layoutWidget);
        label_Name->setObjectName(QStringLiteral("label_Name"));

        gridLayout->addWidget(label_Name, 2, 0, 1, 1);

        label_Image = new QLabel(layoutWidget);
        label_Image->setObjectName(QStringLiteral("label_Image"));

        gridLayout->addWidget(label_Image, 4, 0, 1, 1);

        lineEdit_ID = new QLineEdit(layoutWidget);
        lineEdit_ID->setObjectName(QStringLiteral("lineEdit_ID"));

        gridLayout->addWidget(lineEdit_ID, 0, 1, 1, 1);

        lineEdit_Category = new QLineEdit(layoutWidget);
        lineEdit_Category->setObjectName(QStringLiteral("lineEdit_Category"));

        gridLayout->addWidget(lineEdit_Category, 1, 1, 1, 1);

        label_ID = new QLabel(layoutWidget);
        label_ID->setObjectName(QStringLiteral("label_ID"));

        gridLayout->addWidget(label_ID, 0, 0, 1, 1);

        lineEdit_Date = new QLineEdit(layoutWidget);
        lineEdit_Date->setObjectName(QStringLiteral("lineEdit_Date"));

        gridLayout->addWidget(lineEdit_Date, 3, 1, 1, 1);

        lineEdit_Name = new QLineEdit(layoutWidget);
        lineEdit_Name->setObjectName(QStringLiteral("lineEdit_Name"));

        gridLayout->addWidget(lineEdit_Name, 2, 1, 1, 1);

        label_Date = new QLabel(layoutWidget);
        label_Date->setObjectName(QStringLiteral("label_Date"));

        gridLayout->addWidget(label_Date, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_Delete = new QPushButton(layoutWidget);
        pushButton_Delete->setObjectName(QStringLiteral("pushButton_Delete"));

        gridLayout_2->addWidget(pushButton_Delete, 3, 0, 1, 1);

        pushButton_Back = new QPushButton(layoutWidget);
        pushButton_Back->setObjectName(QStringLiteral("pushButton_Back"));

        gridLayout_2->addWidget(pushButton_Back, 6, 0, 1, 1);

        pushButton_Load = new QPushButton(layoutWidget);
        pushButton_Load->setObjectName(QStringLiteral("pushButton_Load"));

        gridLayout_2->addWidget(pushButton_Load, 5, 0, 1, 1);

        pushButton_Update = new QPushButton(layoutWidget);
        pushButton_Update->setObjectName(QStringLiteral("pushButton_Update"));

        gridLayout_2->addWidget(pushButton_Update, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        pushButton_Save = new QPushButton(layoutWidget);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));

        gridLayout_2->addWidget(pushButton_Save, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        tableView = new QTableView(edit_info);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(300, 530, 941, 331));
        tableView->setMouseTracking(true);
        tableView->setTabletTracking(true);
        label_query = new QLabel(edit_info);
        label_query->setObjectName(QStringLiteral("label_query"));
        label_query->setGeometry(QRect(10, 410, 141, 21));
        label_query->setFrameShape(QFrame::Box);
        label_query->setFrameShadow(QFrame::Plain);
        label_pic_table = new QLabel(edit_info);
        label_pic_table->setObjectName(QStringLiteral("label_pic_table"));
        label_pic_table->setGeometry(QRect(10, 570, 281, 261));
        label_pic_table->setFrameShape(QFrame::Box);
        label_pic_table->setLineWidth(1);
        layoutWidget1 = new QWidget(edit_info);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 380, 161, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Rotate = new QPushButton(layoutWidget1);
        pushButton_Rotate->setObjectName(QStringLiteral("pushButton_Rotate"));

        horizontalLayout->addWidget(pushButton_Rotate);

        lineEdit_rotateAngle = new QLineEdit(layoutWidget1);
        lineEdit_rotateAngle->setObjectName(QStringLiteral("lineEdit_rotateAngle"));
        QFont font;
        font.setPointSize(10);
        font.setItalic(true);
        lineEdit_rotateAngle->setFont(font);

        horizontalLayout->addWidget(lineEdit_rotateAngle);

        gridLayoutWidget = new QWidget(edit_info);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(520, 10, 371, 321));
        m_gridLayout = new QGridLayout(gridLayoutWidget);
        m_gridLayout->setObjectName(QStringLiteral("m_gridLayout"));
        m_gridLayout->setContentsMargins(0, 0, 0, 0);
        m_graphicsView = new QGraphicsView(gridLayoutWidget);
        m_graphicsView->setObjectName(QStringLiteral("m_graphicsView"));

        m_gridLayout->addWidget(m_graphicsView, 0, 0, 1, 1);

        m_clippedLabel = new QLabel(edit_info);
        m_clippedLabel->setObjectName(QStringLiteral("m_clippedLabel"));
        m_clippedLabel->setGeometry(QRect(1000, 100, 211, 231));
        m_clippedLabel->setFrameShape(QFrame::NoFrame);
        m_clippedLabel->setFrameShadow(QFrame::Plain);
        m_clippedLabel->setLineWidth(3);
        layoutWidget2 = new QWidget(edit_info);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(230, 300, 256, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_showImage = new QPushButton(layoutWidget2);
        pushButton_showImage->setObjectName(QStringLiteral("pushButton_showImage"));
        QFont font1;
        font1.setPointSize(10);
        pushButton_showImage->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_showImage);

        pushButton_openImage = new QPushButton(layoutWidget2);
        pushButton_openImage->setObjectName(QStringLiteral("pushButton_openImage"));
        pushButton_openImage->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_openImage);

        pushButton_Crop = new QPushButton(layoutWidget2);
        pushButton_Crop->setObjectName(QStringLiteral("pushButton_Crop"));
        pushButton_Crop->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_Crop);

        pushButton_deletePoints = new QPushButton(edit_info);
        pushButton_deletePoints->setObjectName(QStringLiteral("pushButton_deletePoints"));
        pushButton_deletePoints->setGeometry(QRect(890, 40, 101, 25));
        layoutWidget3 = new QWidget(edit_info);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(571, 340, 254, 27));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_pushButton_Add = new QPushButton(layoutWidget3);
        m_pushButton_Add->setObjectName(QStringLiteral("m_pushButton_Add"));

        horizontalLayout_3->addWidget(m_pushButton_Add);

        m_pushButton_Save = new QPushButton(layoutWidget3);
        m_pushButton_Save->setObjectName(QStringLiteral("m_pushButton_Save"));

        horizontalLayout_3->addWidget(m_pushButton_Save);

        pushButton_Undo = new QPushButton(layoutWidget3);
        pushButton_Undo->setObjectName(QStringLiteral("pushButton_Undo"));

        horizontalLayout_3->addWidget(pushButton_Undo);

        pushButton_deletePoints_2 = new QPushButton(edit_info);
        pushButton_deletePoints_2->setObjectName(QStringLiteral("pushButton_deletePoints_2"));
        pushButton_deletePoints_2->setGeometry(QRect(230, 340, 111, 25));
        QWidget::setTabOrder(lineEdit_ID, lineEdit_Category);
        QWidget::setTabOrder(lineEdit_Category, lineEdit_Name);
        QWidget::setTabOrder(lineEdit_Name, lineEdit_ImageName);
        QWidget::setTabOrder(lineEdit_ImageName, pushButton_Delete);
        QWidget::setTabOrder(pushButton_Delete, pushButton_Update);
        QWidget::setTabOrder(pushButton_Update, pushButton_Load);
        QWidget::setTabOrder(pushButton_Load, pushButton_Back);
        QWidget::setTabOrder(pushButton_Back, pushButton_showImage);
        QWidget::setTabOrder(pushButton_showImage, tableView);

        retranslateUi(edit_info);

        QMetaObject::connectSlotsByName(edit_info);
    } // setupUi

    void retranslateUi(QDialog *edit_info)
    {
        edit_info->setWindowTitle(QApplication::translate("edit_info", "Dialog", nullptr));
        label_showImage->setText(QApplication::translate("edit_info", "                         Show Image", nullptr));
        label_Status->setText(QApplication::translate("edit_info", "Database Status", nullptr));
        groupBox->setTitle(QApplication::translate("edit_info", "Info", nullptr));
        lineEdit_ImageName->setText(QString());
        label_Category->setText(QApplication::translate("edit_info", "Category", nullptr));
        label_Name->setText(QApplication::translate("edit_info", "Name", nullptr));
        label_Image->setText(QApplication::translate("edit_info", "Image Path", nullptr));
        label_ID->setText(QApplication::translate("edit_info", "ID", nullptr));
        lineEdit_Date->setText(QApplication::translate("edit_info", "dd.mm.yyyy", nullptr));
        label_Date->setText(QApplication::translate("edit_info", "Date", nullptr));
        pushButton_Delete->setText(QApplication::translate("edit_info", "Delete", nullptr));
        pushButton_Back->setText(QApplication::translate("edit_info", "Back", nullptr));
        pushButton_Load->setText(QApplication::translate("edit_info", "Load", nullptr));
        pushButton_Update->setText(QApplication::translate("edit_info", "Update", nullptr));
        pushButton_Save->setText(QApplication::translate("edit_info", "Save", nullptr));
        label_query->setText(QString());
        label_pic_table->setText(QApplication::translate("edit_info", "               Pic Display from Table", nullptr));
        pushButton_Rotate->setText(QApplication::translate("edit_info", "Rotate", nullptr));
#ifndef QT_NO_WHATSTHIS
        lineEdit_rotateAngle->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lineEdit_rotateAngle->setInputMask(QString());
        lineEdit_rotateAngle->setText(QString());
        m_clippedLabel->setText(QApplication::translate("edit_info", "                  Crop Label", nullptr));
        pushButton_showImage->setText(QApplication::translate("edit_info", "Show Image", nullptr));
        pushButton_openImage->setText(QApplication::translate("edit_info", "Open Image", nullptr));
        pushButton_Crop->setText(QApplication::translate("edit_info", "Open Crop", nullptr));
        pushButton_deletePoints->setText(QApplication::translate("edit_info", "Delete Points", nullptr));
        m_pushButton_Add->setText(QApplication::translate("edit_info", "Add file", nullptr));
        m_pushButton_Save->setText(QApplication::translate("edit_info", "Save", nullptr));
#ifndef QT_NO_STATUSTIP
        pushButton_Undo->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushButton_Undo->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        pushButton_Undo->setText(QApplication::translate("edit_info", "Revert", nullptr));
        pushButton_deletePoints_2->setText(QApplication::translate("edit_info", "Delete Points 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_info: public Ui_edit_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_INFO_H
