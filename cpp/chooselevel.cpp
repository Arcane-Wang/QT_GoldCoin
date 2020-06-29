#include "chooselevel.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<mainscene.h>
#include<QTimer>
#include<QLabel>
#include<QTextFormat>
#include<QSound>
#include<QDialog>
#include<QMessageBox>
ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle(QStringLiteral("选择关卡"));
    //创建菜单栏
    QMenuBar *menu=menuBar();
    setMenuBar(menu);

    //创建开始菜单
    QMenu *startMenu= menu->addMenu(QStringLiteral("开始"));

    //游戏规则
    QAction *ruleAction=startMenu->addAction(QStringLiteral("游戏规则"));
    connect(ruleAction,&QAction::triggered,[=](){
       showDialog();
    });
    //创建退出菜单栏
    QAction *quitAction=startMenu->addAction(QStringLiteral("退出游戏"));
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        qDebug()<<"clicked back button";
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->returnMain();
        });

    });

    for(int i=0;i<20;i++){
        MyPushButton * menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*70+25,i/4*70+130);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();
            qDebug()<<"choosing round: "<<QString("%1").arg(i+1).toUtf8().data();
            menuBtn->zoom1();
            menuBtn->zoom2();
            QTimer::singleShot(500,this,[=](){

                //将当前选关隐藏
                this->hide();
                //显示游戏场景
                play=new PlayScene(i+1);
                play->setGeometry(this->geometry());
                play->show();
                connect(play,&PlayScene::returnPre,[=](){
                    //设置场景在屏幕上的位置不变
                    this->setGeometry(play->geometry());
                    this->show();
                    delete play;
                    play=NULL;
                    qDebug()<<"test!";
                });
            });
        });


        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        //        label->move(25+i%4*70+menuBtn->width()*0.5,i/4*70+130);
        label->move(25+i%4*70,i/4*70+130);
        //设置label上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置字体大小和颜色
        label->setStyleSheet("font-size:20px;color:red");
        //设置字体样式
        QFont font(QStringLiteral("Times New Roman"),20,QFont::Bold);
        label->setFont(font);
        //设置鼠标穿透事件，防止被label挡住
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}
void ChooseLevel::showDialog(){
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
void ChooseLevel::paintEvent(QPaintEvent*){
    //创建画家
    QPainter painter(this);
    //创建QPixmap 对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/OtherSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//此处width和height设置成被拉伸成和窗口一样大
    //加载图标
    pix.load(":/res/Title.png");

    //绘制
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);




}
