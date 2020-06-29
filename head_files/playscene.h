#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<dataconfig.h>
#include<mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int);
    int levelIndex;//记录所选关卡
    void paintEvent(QPaintEvent*);
    int gameArray[4][4]; //二维数组，维护当前二维数组
    MyCoin * btnCoin[4][4];
    bool isWin;
    void showDialog();
signals:
    void returnPre();

};

#endif // PLAYSCENE_H
