#include "mainscence.h"
#include "ui_mainscence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QDebug>
#include<QSound>




MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);

   // 配置主场景

    // 设置固定大小
    setFixedSize(320, 588);

    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    setWindowTitle("翻金币主场景");

    // 退出按钮实现

    connect(ui->actionQuit,&QAction::triggered,[=](){

        this->close();
    });

    // 开始按钮音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    // 准备开始按钮的

    MypushButton * startBtn = new MypushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    // 选择关卡场景
    chooseScene = new ChooseLevelScenece;

    // 监听选择关卡那妞
    connect(chooseScene, &ChooseLevelScenece::chooseSceneBack,this,[=](){

        setGeometry(chooseScene->geometry());//每次切换场景都保持位置一致
        chooseScene->hide(); // 隐藏场景关卡
        this->show(); // 显示选择关卡场景
    });

    connect(startBtn, &MypushButton::clicked,[=](){
        qDebug()<<"点击了开始";

        //播放开始音效
        // startSound->setLoops(10); //设置循环播放次数 -1无限循环
        startSound->play();


        // 按钮弹起特效

        //startBtn->zoom1();
        startBtn->zoom2();

        // 延时进入到关卡场景中


//        QTimer::singleShot(500,this,[=](){


            //进入关卡场景
            //自身隐藏
         // chooseScene->setGeometry(this->geometry());//每次切换场景都保持位置一致

            this->hide();
           chooseScene->setGeometry(this->geometry());//每次切换场景都保持位置一致

            chooseScene->show();

//        });


    });

}

void MainScence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/res/Title.png");

    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);

    painter.drawPixmap(10,30,pix);
}



MainScence::~MainScence()
{
    delete ui;
}
