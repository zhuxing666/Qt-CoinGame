#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"


class playScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playScene(QWidget *parent = 0);
    playScene(int levelNum);

    int levelIndex ; // 记录所选关卡

    // 重写背景事件
    void paintEvent(QPaintEvent *);

    // 二维数组 维护每个关卡的具体数据

    int gameArray[4][4];
    MyCoin * CoinBtn[4][4];


    //是否胜利的标志
    bool isWin;


signals:
    // 写一个自定义信号
    void chooseSceneBack();

public slots:

};

#endif // PLAYSCENE_H
