#include "playscene.h"
#include<QDebug>
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QTimer>
#include<QPropertyAnimation>
#include<QSound>

//playScene::playScene(QWidget *parent) :
//    QMainWindow(parent)
//{
//}

playScene::playScene(int levelNum)
{
    // 初始化字符串
    QString str = QString("进入第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    // 初始化游戏场景
    //设置固定大小
    this->setFixedSize(320, 588);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle(QString("翻金币场景 %1").arg(levelNum));

    // 创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    // 创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");


    // 创建退出 菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出实现退出游戏

    connect(quitAction,&QAction::triggered,[=](){

        this->close();

    });

    // 添加音效资源
    //返回
    QSound * BackSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);



    // 返回按钮
    MypushButton * backBtn = new MypushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());

    // 点击返回按钮
    connect(backBtn,&MypushButton::clicked,[=](){
        qDebug()<<"翻金币中返回返回按钮";

        // 播放返回按钮音效
        BackSound->play();
        // 告诉翻金币场景我返回了
        emit this->chooseSceneBack();
       // QTimer::singleShot()



    });


    // 显示当前关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);

    // 将字体设置到标签中

    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height() - 50,120, 50);

    dataConfig config;
    // 初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j <4;j++)
        {
            this->gameArray[i][j]= config.mData[this->levelIndex][i][j];
        }
    }

    // 胜利图片显示
    QLabel * winLable = new QLabel;
    QPixmap tmpix;
    tmpix.load(":/res/LevelCompletedDialogBg.png");
    winLable->setGeometry(0,0,tmpix.width(),tmpix.height());
    winLable->setPixmap(tmpix);
    winLable->setParent(this);
    winLable->move((this->width() - tmpix.width() )* 0.5, -tmpix.height());

    //显示金币背景图案
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //绘制背景图片

            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //创建金币
            if(this->gameArray[i][j] == 1)
            {
                // 显示金币
                str = ":/res/Coin0001.png";

            }

            else {
                str = ":/res/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);


            // 给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; // 1正面 0反面

            //将金币放入到 金币的二维数组里 以便后期的维护
            CoinBtn[i][j] = coin;


            // 点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){

                // 播放翻金币音效
                flipSound->play();

                // 点击按钮 将所有按钮都先禁用
                for(int i =0; i < 4;i++)
                {
                    for(int j = 0; j <4;j++)
                    {
                       this->CoinBtn[i][j]->isWin = true;
                    }
                }



                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0?1:0;

                //翻转周围金币

                // 翻转金币延时功能 可能有问题版本问题不识别singshot + lambda 这边注释掉了

//                QTimer::singleShot(300,this,[=](){


                    if(coin-> posX + 1 <=3) //周围的右侧金币翻转的条件
                    {
                        CoinBtn[coin->posX+1][coin->posY]->changeFlag();
                         this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0?1:0;

                    }
                    //周围的左侧硬币翻转的条件
                    if(coin->posX - 1 >=0)
                    {
                        CoinBtn[coin->posX-1][coin->posY]->changeFlag();
                         this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0?1:0;
                    }

                    //周围上侧翻转条件
                    if(coin->posY + 1 <=3)
                    {
                        CoinBtn[coin->posX][coin->posY+1]->changeFlag();
                         this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0?1:0;
                    }

                    //周围上侧翻转条件
                    if(coin->posY -1 >=0)
                    {
                        CoinBtn[coin->posX][coin->posY-1]->changeFlag();
                         this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0?1:0;
                    }
                    //翻完周围金币 将所有金币解开禁用
                    for(int i =0; i < 4;i++)
                    {
                        for(int j = 0; j <4;j++)
                        {
                           this->CoinBtn[i][j]->isWin = false;
                        }
                    }




                    // 判断是否胜利
                    this->isWin = true;
                    for(int i =0; i < 4;i++)
                    {
                        for(int j = 0; j <4;j++)
                        {
                            if(CoinBtn[i][j]->flag == false) // 只要有一个是反面 就算是失败
                            {

                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if(this->isWin == true)
                    {
                        //添加胜利音效
                        winSound->play();
                        //胜利了
                        qDebug() <<"游戏胜利";
                        //将所有按钮的胜利标志改为true 如果再次点击return 不响应
                        // 判断是否胜利
                        this->isWin = true;
                        for(int i =0; i < 4;i++)
                        {
                            for(int j = 0; j <4;j++)
                            {
                               CoinBtn[i][j]->isWin = true;
                            }
                        }
                        // 将胜利的图片下降来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLable,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        // 设置开始位置
                        animation->setStartValue(QRect(winLable->x(),winLable->y(),winLable->width(),winLable->height()));

                        //设置结束位置
                        animation->setEndValue(QRect(winLable->x(),winLable->y()+114,winLable->width(),winLable->height()));


                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);

                        //执行动画
                        animation->start();


                    }

                });

//          });
        }
    }



}

// 重写背景事件
void playScene::paintEvent(QPaintEvent *)
{
    // 创建背景
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    // 加载标题

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
