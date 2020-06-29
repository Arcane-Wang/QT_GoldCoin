#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    //normalImgPath 保存正常显示图片路径
    normalImgPath=normalImg;
    //成员pressedImgPath 保存按下后显示的图片路径
    pressedImgPath=pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断能否加载正常显示的图片，不能的话提示失败
    bool ret=pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"Failed to load the picture!";
        return;
    }
    //设置图片尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());

    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:Opx;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}


//创建按钮动画效果
void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animat1=new QPropertyAnimation(this,"geometry");
    animat1->setDuration(300);
    animat1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animat1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animat1->setEasingCurve(QEasingCurve::OutBounce);
    animat1->start();
}

void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation *animat1=new QPropertyAnimation(this,"geometry");
    animat1->setDuration(300);
    animat1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animat1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animat1->setEasingCurve(QEasingCurve::OutBounce);
    animat1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){

    if(this->pressedImgPath!=""){
        //传入的图片不为空，说明有需要按下状态，切图
        QPixmap pixmap;
        bool ret=pixmap.load(pressedImgPath);
        if(!ret){
            qDebug()<<pressedImgPath<<"Failed to load the picture!";
            return;
        }
        //设置图片尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){

    if(this->normalImgPath!=""){
        //传入的图片不为空，说明有需要按下状态，切图
        QPixmap pixmap;
        bool ret=pixmap.load(normalImgPath);
        if(!ret){
            qDebug()<<normalImgPath<<"Failed to load the picture!";
            return;
        }
        //设置图片尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
