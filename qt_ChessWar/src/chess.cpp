#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QDebug>
#include <windows.h>
#include "chess.h"

chess::chess(QWidget *parent) : QPushButton(parent)
{
}

void chess::pos_init() //正常状态下一个位置的贴图
{
    QString path;
    QString ground[4] = {"road", "block", "spines", "swamp"};
    QString plant[5] = {" ", "Chomper", "NutWall", "Sunflower", "FumeShroom"};
    QString enemy[5] = { "", "Rider", "Rock", "Spray", "boss"};
// :/map/icons/map/road.png
    if(!is_plant && !is_enemy)
    {
        path = ":/map/icons/map/" + ground[pos_kind] + ".png";
    }
    else if(is_plant)
    {
        path = ":/map/icons/map/" + plant[plant_kind] + "/" + ground[pos_kind] + "_" + plant[plant_kind] + "0.png";
    }
    else if(is_enemy)
    {
        path = ":/map/icons/map/" + enemy[enemy_kind] + "/" + ground[pos_kind] + "_" + enemy[enemy_kind] + "0.png";
    }
//    qDebug()<<"x: "<<x<<"y: "<<y<<"pos_init()"<<endl;
    QIcon icon(path);
    this->setIcon(icon);
    this->setIconSize(QSize(60, 60));
}

void chess::be_light()
{
    QString newpath;
    QString ground[4] = {"road", "block", "spines", "swamp"};
    QString plant[5] = {" ", "Chomper", "NutWall", "Sunflower", "FumeShroom"};
    QString enemy[5] = { "", "Rider", "Rock", "Spray", "boss"};
    if(!lighted) //如果未亮起
    {
        if(pos_kind!=1)
        {
            lighted = true; // 则亮起并且lighted属性为真
            if(!is_enemy&&!is_plant)
            {
    //            :/map/icons/map/road_light.png
                newpath = ":/map/icons/map/" + ground[pos_kind] + "_light.png";
            }
            else if(is_plant)
            {
                newpath = ":/map/icons/map/" + plant[plant_kind] + "/" + ground[pos_kind] + "_" + plant[plant_kind] + "0_light.png";
            }
            else if(is_enemy)
            {
                newpath = ":/map/icons/map/" + enemy[enemy_kind] + "/" + ground[pos_kind] + "_" +enemy[enemy_kind] + "0_light.png";
            }
//            qDebug()<<x<<" "<<y<<" lighted!";
            QIcon icon(newpath);
            this->setIcon(icon);
            this->setIconSize(QSize(60, 60));
        }
    }
}

void chess::not_be_light()
{
    if(lighted)
    {
        lighted = false;
        pos_init();
//        qDebug()<<"Stop light!";
    }
}

bool chess::chess_select_1 = false; // 默认全局没有棋子被选中

void chess::be_select() //棋子被点击后的信号
{
//    qDebug()<<x<<" "<<y<<" is clicked!"<<endl;
//    qDebug()<<"chess_select_1: "<<chess_select_1<<endl;
//    qDebug()<<"selected: "<<selected<<" pos_kind: "<<pos_kind<<endl;
    if(!selected && pos_kind != 1) // 如果这个棋子没有被选中 且格子不可以是block才可以被选中
    {
//        qDebug()<<"be_select_s0"<<endl;
        if(!chess_select_1 && (is_enemy || is_plant)) // 如果它是敌人或者角色才能被选中为第一个被选中棋子
        {
//            qDebug()<<"be_select_s1"<<endl;
            selected = true; // 被选中的棋子的selected会变成被选中
            chess_select_1 = true; // 全局会显示有一个棋子被选中
            be_light(); // 第一个被选中的棋子会亮起 （TODO：这里可能会改）
//            qDebug()<<"chess_select_1: "<<chess_select_1<<endl;
            emit crood(x, y); // 发送第一个被选中的棋子的信号到gamemode进行后续操作
        }
        else if(chess_select_1 && lighted) // 如果第一个棋子已经被选中了 那就只能在亮起的地方选第二个棋子
        {
            chess_select_1 = false;
//            qDebug()<<"be_select_s2"<<endl;
           emit crood(x, y); // 第二个棋子是第一个棋子的目标 可以是地形(move)或者角色(atk/ mag)
           // gamemode中保存了第一个棋子的坐标 所以在gamemode中会清除第一个的棋子的选中属性
           // 清除第一个棋子的方法是用be_select再次选中那个棋子 就会取消选中
        }
    }
    else if(selected)// selected == true 如果这个棋子已经被选中了 那么再次点击就是取消选中
    {
//        qDebug()<<"be_select_s3"<<endl;
        selected = false; // 取消选中属性
        chess_select_1 = false; // 恢复全局没有棋子被选中
        not_be_light(); // 取消亮起
//        qDebug()<<"chess_select_1: "<<chess_select_1<<endl;
        emit crood(x, y); //发送信号到gamemode取消ui界面的属性显示和清空gamemode的操作状态
    }
}

void chess::skip_slot()
{
    chess_select_1 = false;
}

void chess::be_attacked_start()
{
    qDebug()<<"Icon should be changed!";
    QString newpath;
    QString ground[4] = {"road", "block", "spines", "swamp"};
    QString plant[5] = {" ", "Chomper", "NutWall", "Sunflower", "FumeShroom"};
    QString enemy[5] = { "", "Rider", "Rock", "Spray", "boss"};

    if(is_enemy)
    {
        // :/map/icons/map/boss/road_boss0_ATK.png
//        qDebug() << "I have tried to change the Icon" ;
        newpath = ":/map/icons/map/"+enemy[enemy_kind]+"/"+ground[pos_kind]+"_"+enemy[enemy_kind]+"0_ATK.png";
    }
    else if(is_plant)
    {
        newpath = ":/map/icons/map/"+plant[plant_kind]+"/"+ground[pos_kind]+"_"+plant[plant_kind]+"0_ATK.png";
    }

    QIcon icon(newpath);
    this->setIcon(icon);
    this->setIconSize(QSize(60, 60));
}

