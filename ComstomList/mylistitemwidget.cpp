#include "mylistitemwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

static int deleteBtnWidth = 60;

MyListItemWidget::MyListItemWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void MyListItemWidget::setData(HHItemData *aData)
{
    data = aData;

    QPixmap myPix(data->iconPath);
    icon->setPixmap(myPix);
    name->setText(data->name);
    introduce->setText(data->introduction);
}

void MyListItemWidget::setupUI()
{
    icon = new QLabel(this);
    icon->setFixedSize(60, 60);
    icon->setScaledContents(true);
    icon->setStyleSheet("QLabel{padding-left:5px;padding-right:5px;padding-top:5px;padding-bottom:5px;}");


    QWidget *fontArea = new QWidget(this);

    name = new QLabel(fontArea);
    name->setFont(QFont("Times", 10, QFont::Bold));
    name->setStyleSheet("QLabel{padding-left:5px;padding-right:5px;}");

    introduce = new QLabel(fontArea);
    introduce->setFont(QFont("Times", 10, QFont::Bold));
    introduce->setStyleSheet("QLabel{padding-left:5px;padding-right:5px;}");
    introduce->setWordWrap(true);

    QVBoxLayout *verLayout = new QVBoxLayout;
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setMargin(0);
    verLayout->setSpacing(0);
    verLayout->addWidget(name);
    verLayout->addWidget(introduce);
    fontArea->setLayout(verLayout);


    deleteBtn = new QPushButton(this);
    deleteBtn->setText("删除");
    deleteBtn->setFixedSize(deleteBtnWidth, 70);
    deleteBtn->setStyleSheet("QPushButton{background-color:red;\
                              color: white;}");
    connect(deleteBtn, &QPushButton::clicked, this, &MyListItemWidget::delecteButtonClick);

    QHBoxLayout *horLayout = new QHBoxLayout;
    horLayout->setContentsMargins(0, 0, deleteBtnWidth, 0);
    horLayout->setMargin(0);
    horLayout->setSpacing(0);
    horLayout->addWidget(icon);
    horLayout->addWidget(fontArea);
    horLayout->addWidget(deleteBtn);
    this->setLayout(horLayout);
}


void MyListItemWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) {
        pressPoint = e->globalPos();
    }
}

void MyListItemWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton) {
        int offset = pressPoint.x() - e->globalX();
        if(offset < 0) {
            return;
        }
        if(offset > 0 && offset < deleteBtnWidth / 2) {
            QRect frame = geometry();
            frame.moveLeft(-offset);
            setGeometry(frame);
        } else {
            QRect frame = geometry();
            frame.moveLeft(-deleteBtnWidth);
            setGeometry(frame);
        }
    }
}

void MyListItemWidget::mouseReleaseEvent(QMouseEvent *e)
{

    if(e->button() == Qt::LeftButton) {
        qDebug() << "mouseReleaseEvent";
        int offset = pressPoint.x() - e->globalX();
        if(offset < deleteBtnWidth / 2) {
            QRect frame = geometry();
            frame.moveLeft(0);
            setGeometry(frame);
        }
    }
}

void MyListItemWidget::delecteButtonClick()
{
    emit deleteItem(data);
}
