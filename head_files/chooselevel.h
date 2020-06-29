#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include<playscene.h>
class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    PlayScene * play=NULL;
    void showDialog();


signals:
    void returnMain();
    //游戏场景对象指针

};

#endif // CHOOSELEVEL_H
