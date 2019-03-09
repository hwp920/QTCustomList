#ifndef MYLISTITEMWIDGET_H
#define MYLISTITEMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

//typedef struct {
//    QString iconPath;
//    QString name;
//    QString introduction;
//} HHItemData;

class HHItemData
{
public:
     QString iconPath;
     QString name;
     QString introduction;



};

class MyListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListItemWidget(QWidget *parent = nullptr);

    void setData(HHItemData *data);

signals:
    void deleteItem(HHItemData *);

public slots:


protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


    void delecteButtonClick();

private:
    HHItemData  *data;

    QPoint      pressPoint;

    QPushButton *deleteBtn;
    QLabel      *icon;
    QLabel      *name;
    QLabel      *introduce;

private:
    void setupUI();
};

#endif // MYLISTITEMWIDGET_H
