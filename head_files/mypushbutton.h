#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QString>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
//normalImg 正常显示的图片
   MyPushButton(QString normalImg,QString pressImg="");
   QString normalImgPath;
   QString pressedImgPath;
   void zoom1();
   void zoom2();
   //重写按钮 按下 以及 释放 事件
   void mousePressEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
