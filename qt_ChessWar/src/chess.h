#ifndef CHESS_H
#define CHESS_H

#include <QPushButton>
#include <QWidget>

class chess : public QPushButton
{
    Q_OBJECT

public:
    chess(QWidget* parent);

    static bool chess_select_1; // 显示整个棋盘有没有棋子被选中(第一个棋子
    int x, y;

    void pos_init();

    bool is_plant = false;
    bool is_enemy = false;
    int pos_kind = 0; //这块地的类型：1.普通 2.墙 3.刺 4.泥地
    int plant_kind = 0; //植物类型：1.食人花（普通） 2.坚果（肉） 3.太阳花（奶） 4.大喷菇（射手）
    QString plant_name;
    int enemy_kind = 0; //敌人类型：1.普通 2.肉 3.射手 4.BOSS
    QString enemy_name;
    int MAX_HP = 0;
    int hp = 0;
    int sp = 0;
    int atk = 0;
    int mag = 0;
    int range = 0; //射程
    int speed = 0; //速度（走多远:3, 2, 2, 2

    bool selected = false; //单个棋子有没有被选中
    bool lighted = false; //棋子有没有亮起

    bool have_atk = false;
    bool have_move = false;

    bool should_not_place = false;

    void be_light(); //让棋子亮起
    void not_be_light(); //让棋子不亮

    void be_attacked_start();

signals:
    void crood(int, int); //向gamemode发送正在操作的棋子的定位

public slots:
    void be_select(); //棋子被选中（？
    void skip_slot();



};

#endif // CHESS_H
