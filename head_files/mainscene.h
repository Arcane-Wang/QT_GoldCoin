#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<chooselevel.h>
QT_BEGIN_NAMESPACE
namespace Ui { class mainscene; }
QT_END_NAMESPACE

class mainscene : public QMainWindow
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = nullptr);
    ~mainscene();
    void paintEvent(QPaintEvent*);
    ChooseLevel * chooselevel=NULL;
    void showDialog();
private:
    Ui::mainscene *ui;
};
#endif // MAINSCENE_H
