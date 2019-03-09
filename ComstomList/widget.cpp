#include "widget.h"
#include "ui_widget.h"
#include <QListWidget>
#include "mylistitemwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

const QStringList icons = {
    ":/images/li.jpg",  ":/images/yang.jpg", ":/images/zhang.jpg"
};
const QStringList singers = {
    "李荣浩", "杨千嬅", "张震岳"
};
const QStringList introduces = {
    "李荣浩，1985年7月11日出生于安徽省蚌埠市，中国流行乐男歌手、音乐制作人、吉他手、演员。",
    "杨千嬅，原名杨泽嬅，1974年2月3日出生于中国香港，香港流行女歌手、影视演员，毕业于香港理工大学。",
    "张震岳，1974年5月2日出生，中国台湾男歌手。"
};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
//    setAttribute(Qt::WA_TranslucentBackground);
//    ui->contentWidget->setAttribute(Qt::WA_TranslucentBackground, false);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::addItem()
{
    QListWidget *list = ui->listWidget;

    qDebug() << "on_addButton_clicked()";
    int index = qrand() % 3;

    HHItemData *itemData = new HHItemData();
    itemData->name = singers.at(index);
    itemData->introduction = introduces.at(index);
    itemData->iconPath = icons.at(index);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(list->width() + 60, 70));
    list->addItem(item);

    MyListItemWidget *w = new MyListItemWidget(list);
    w->setData(itemData);
    list->setItemWidget(item, w);

    connect(w, &MyListItemWidget::deleteItem, this, &Widget::delecteItem);
    datas.append(itemData);
}

 void Widget::paintEvent(QPaintEvent *)
 {
     QPainter p(this);
     p.drawPixmap(0, 0, QPixmap(":/images/iphone_bg.png"), 0, 0, 391, 780);
 }


 void Widget::mousePressEvent(QMouseEvent *e)
 {
     if(e->button() == Qt::LeftButton) {

         qDebug() << ui->listWidget->currentItem();
         pressPoint = e->globalPos() - this->frameGeometry().topLeft();

     } else if (e->button() == Qt::RightButton) {

         close();
    }
 }


 void Widget::mouseMoveEvent(QMouseEvent *e)
 {
     if(e->buttons() & Qt::LeftButton) {
         move(e->globalPos() - pressPoint);
     }
 }

void Widget::on_addButton_clicked()
{
    addItem();
}

void Widget::delecteItem(HHItemData *data)
{
    int index = datas.indexOf(data);
    qDebug() << "delecteItem:" << index;
    delete ui->listWidget->item(index);

    datas.removeAt(index);
    delete  data;
}
