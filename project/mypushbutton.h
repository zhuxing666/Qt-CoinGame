#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QString>
#include<QDebug>

class MypushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MypushButton(QWidget *parent = 0);

    //构造函数 参数 1正常显示图片  参数2 按下后正常图片路径
    MypushButton(QString normalImg, QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    // 弹跳特效
    void zoom1(); // 向下跳

    void zoom2(); // 向上

    // 重写按钮的 按下 和释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:

};

#endif // MYPUSHBUTTON_H
