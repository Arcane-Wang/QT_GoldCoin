#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include<QPropertyAnimation>
#include<QSound>
#include<QDialog>
#include<QMessageBox>
PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int levelNum){
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    qDebug()<<"Entering round"<<QString("%1").arg(levelNum);
    this->levelIndex=levelNum;
    //配置游戏关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle(QStringLiteral("游戏中"));
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
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        qDebug()<<"clicked back button";
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->returnPre();
        });

    });

    //显示当前关卡
    QLabel * round=new QLabel;
    round->setParent(this);
    round->setText(QString::number(this->levelIndex));
    round->setGeometry(30,this->height()-50,200,50);  //创建QLabel 的显示区域，此处为一矩形范围
    round->setText(QStringLiteral("当前关卡:")+QString("%1").arg(levelIndex));
    round->setStyleSheet("font-size:30px;color:blue");
    QFont font(QStringLiteral("方正舒体"),30,QFont::Bold);
    round->setFont(font);

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }
    //胜利后显示的图片
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //创建金币背景图片
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制背景图片
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel * label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //金币对象
            QString str;
            if(this->gameArray[i][j]==1){
                str=":/res/Coin0001.png";
            }
            else
                str=":/res/Coin0008.png";
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);

            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag =gameArray[i][j]; //记录正反标志
            btnCoin[i][j]=coin;
            //点击金币，进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                flipSound->play();
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        this->btnCoin[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
                //翻转周围硬币,延时翻转周围
                QTimer::singleShot(150,this,[=](){
                    if((coin->posX==0&&coin->posY==0)||(coin->posX==3&&coin->posY==3)){
                        for(int i=0;i<4;i++){
                            if(i==coin->posX)
                                continue;
                            else{
                                btnCoin[i][i]->changeFlag();
                                this->gameArray[i][i]=this->gameArray[i][i]==0?1:0;
                            }

                        }
                    }
                    else if(((coin->posX==0&&coin->posY==3)||(coin->posX==3&&coin->posY==0))){
                        for(int i=0;i<4;i++){
                            if(i==coin->posX)
                                continue;
                            else{
                                btnCoin[i][3-i]->changeFlag();
                                this->gameArray[i][3-i]=this->gameArray[i][3-i]==0?1:0;
                            }

                        }
                    }
                    else{
                    if(coin->posX+1<=3){
                        //右侧金币翻转条件
                        btnCoin[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0){
                        //左侧金币翻转条件
                        btnCoin[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY-1>=0){
                        //上侧金币翻转条件
                        btnCoin[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }


                    if(coin->posY+1<=3){
                        //下侧金币翻转条件
                        btnCoin[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    }
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            this->btnCoin[i][j]->isWin=false;
                        }
                    }
                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            qDebug() << btnCoin[i][j]->flag ;
                            if( btnCoin[i][j]->flag == false)
                            {
                                this->isWin = false;
                                //break;
                            }
                        }
                    }
                    if(this->isWin==true){
                        qDebug()<<"Win!!!";
                        //禁用所有按钮点击事件
                        for(int i = 0 ; i < 4;i++)
                        {
                            for(int j = 0 ; j < 4; j++)
                            {
                                btnCoin[i][j]->isWin = true;
                            }
                        }
                        winSound->play();
                    }
                    if(this->isWin)
                    {
                        //qDebug() << "胜利";
                        QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+180,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }


                });


            });

        }
    }



}
void PlayScene::showDialog(){
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
void PlayScene::paintEvent(QPaintEvent*){
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

    //绘制
    painter.drawPixmap(10,30,pix.width()*0.5,pix.height()*0.5,pix);




}
