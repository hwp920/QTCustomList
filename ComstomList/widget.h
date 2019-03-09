#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mylistitemwidget.h"
#include <QVector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:

    void on_addButton_clicked();
    void delecteItem(MyListItemWidget *, HHItemData *);

private:
    void addItem();

private:
    Ui::Widget *ui;

    QPoint      pressPoint;
    QVector<HHItemData *>  datas;
    MyListItemWidget *currentWidget;
};

#endif // WIDGET_H
