#ifndef CHOOSELEVELSCENECE_H
#define CHOOSELEVELSCENECE_H

#include <QMainWindow>
#include"playscene.h"


class ChooseLevelScenece : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScenece(QWidget *parent = 0);

    // 重写绘图事件
    void paintEvent(QPaintEvent *);

    // 游戏场景对象指针
    playScene * play = NULL;

signals:
    // 写一个自定义信号
    void chooseSceneBack();

public slots:

};

#endif // CHOOSELEVELSCENECE_H
