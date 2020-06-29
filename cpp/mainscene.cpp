#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<chooselevel.h>
#include<QSound>
#include<QDialog>
#include<QMessageBox>
mainscene::mainscene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainscene)
{
    ui->setupUi(this);
    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle(QStringLiteral("Welcome to 翻金币"));
    //游戏规则
    connect(ui->actionRules,&QAction::triggered,[=](){
       showDialog();
    });
    //退出功能
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //添加音效
//    QPushButton* btn1=new QPushButton("test",this);
    MyPushButton* startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",startBtn);
//    qDebug()<<this->width()<<", "<<this->height();
//     qDebug()<<startBtn->width()<<", "<<startBtn->height();
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    chooselevel=new ChooseLevel;

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"start!";
        startSound->play(); //开始音效
        //做一个弹起的特效
        startBtn->zoom1();//向下跳
        startBtn->zoom2();//向上跳
        //延时0.5秒后
        QTimer::singleShot(600,this,[=](){
            //当前主页面隐藏
            this->hide();
            //设置场景在屏幕上的位置不变
            chooselevel->setGeometry(this->geometry());
            //进入选择关卡场景
            chooselevel->show();
        });

    });

    connect(chooselevel,&ChooseLevel::returnMain,[=](){
        //设置场景在屏幕上的位置不变
        this->setGeometry(chooselevel->geometry());
        this->show();
        qDebug()<<"testttt";
    });


}
    void mainscene::paintEvent(QPaintEvent*){
        //创建画家
        QPainter painter(this);
        //创建QPixmap 对象
        QPixmap pix;
        //加载图片
        pix.load(":/res/PlayLevelSceneBg.png");
        //绘制背景图
        painter.drawPixmap(0,0,this->width(),this->height(),pix);//此处width和height设置成被拉伸成和窗口一样大
        //加载图标
        pix.load(":/res/Title.png");
        //进行缩放
        pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
        //绘制
        painter.drawPixmap(10,30,pix.width(),pix.height(),pix);




    }

    void mainscene::showDialog(){
//        QDialog *dialog=new QDialog;
//        dialog->setAttribute(Qt::WA_DeleteOnClose);
//        dialog->setWindowTitle(QStringLiteral("游戏规则"));
//        dialog->show();
        QMessageBox* message=new QMessageBox;
        QPushButton *ok=message->addButton(QMessageBox::Ok);
        message->setText(QStringLiteral("游戏规则：点击金币或银币，该硬币以及其周围的硬币将一起翻转，玩家将所有银币最终全部翻转为金币时获胜"));
        message->setAttribute(Qt::WA_DeleteOnClose);
        message->show();
        connect(ok,&QPushButton::clicked,message,&QMessageBox::close);
    }

mainscene::~mainscene()
{
    delete ui;
}

