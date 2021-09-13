#include "mainscence.h"
#include <QApplication>
#include"dataconfig.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScence w;
    w.show();

//    // 测试关卡数据
//    dataConfig config;
//    for(int i = 0; i < 4; i++)
//    {
//        for( int j = 0; j <4; j++)
//        {
//            qDebug()<<config.mData[i][j];
//        }
//        qDebug()<<" ";
//    }

    return a.exec();
}
