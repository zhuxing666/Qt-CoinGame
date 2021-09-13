#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

//MypushButton::MypushButton(QWidget *parent) :
//    QPushButton(parent)
//{

//}
//构造函数 参数 1正常显示图片  参数2 按下后正常图片路径
MypushButton::MypushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;

    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    // 设置图片大小
    this->setFixedSize(pix.width(), pix.height());

    // 设置图片固定样式
   this->setStyleSheet("QPushButton{border:0px;}");

    // 设置图标

    this->setIcon(pix);

    //设置图标大小

    this->setIconSize(QSize(pix.width(),pix.height()));


}

// 弹跳特效
void MypushButton::zoom1() // 向下跳
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    // 设置动画时间间隔
    animation->setDuration(200);

    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y(),this->width(),this->height()));

    // 结束位置


    animation->setEndValue(QRect(this->x(), this->y()+10,this->width(),this->height()));

    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 执行动画
    animation->start();





}

void MypushButton::zoom2() // 向上
{

    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    // 设置动画时间间隔
    animation->setDuration(200);

    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y()+10,this->width(),this->height()));

    // 结束位置


    animation->setEndValue(QRect(this->x(), this->y(),this->width(),this->height()));

    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 执行动画
    animation->start();

}
// 重写按钮的 按下 和释放事件
void MypushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="")  // 传下图片不为空切换
    {



        QPixmap pix;

        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        // 设置图片大小
        this->setFixedSize(pix.width(), pix.height());

        // 设置图片固定样式
       this->setStyleSheet("QPushButton{border:0px;}");

        // 设置图标

        this->setIcon(pix);

        //设置图标大小

        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    // 让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MypushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="")  // 传下图片不为空切换
    {


        QPixmap pix;

        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }

        // 设置图片大小
        this->setFixedSize(pix.width(), pix.height());

        // 设置图片固定样式
       this->setStyleSheet("QPushButton{border:0px;}");

        // 设置图标

        this->setIcon(pix);

        //设置图标大小

        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    // 让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
