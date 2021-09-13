#ifndef MYCOIN_H
#define MYCOIN_H
#include<QTimer>
#include<QDebug>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);

    // 参数 传入金币的路径
    MyCoin(QString btnImg);


    // 金币的属性
    int posX;  //x坐标位置
    int posY;  //y坐标位置
    bool flag; //正反标示

    //改变标志的方法
    void changeFlag();
    QTimer *timer1;  // 正面翻反面定时器
    QTimer *timer2;  //反面翻正面定时器

    int min = 1;
    int max = 8;

    // 执行动画 标志

    bool isAnimation = false;

    // 重写 按下

    void mousePressEvent(QMouseEvent *e);

    //是否胜利的标志
    bool isWin = false;

signals:

public slots:

};

#endif // MYCOIN_H
