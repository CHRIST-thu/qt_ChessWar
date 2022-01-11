#include <QWidget>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QTime>
#include <ctime>
#include <cstdlib>
#include <QDebug>
#include <QMessageBox>
#include <windows.h>
#include "gamemode.h"
#include "ui_gamemode.h"
#include "chess.h"
#include <synchapi.h>
#include <QSound>
#include <QPropertyAnimation>
#include <QMovie>

GameMode::GameMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMode)
{
    ui->setupUi(this);
    this->setWindowTitle("PLANT VS ISSAC");
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    gamemodebgm->play();
    gamemodebgm->setLoops(-1);
}

GameMode::~GameMode()
{
    delete ui;
}

void GameMode::closeEvent( QCloseEvent *)
{
    emit show_main();
}

void GameMode::init_map() //初始化棋盘
{
//    qDebug()<<"mode: "<<mode<<endl;
    int mod_1_map[17][11]= // 初始化棋盘地形 地图1
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    int mod_1_chess[17][11]= // 初始化棋盘棋子属性 地图1
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 8, 1, 3, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 8, 0, 0, 0, 0, 0
    };

    int mod_2_map[17][11]= // 初始化棋盘地形 地图2
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 3, 3, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 3, 3, 0, 0, 0, 0, 0,
        0, 1, 1, 2, 3, 3, 0, 2, 0, 3, 0,
        0, 1, 1, 2, 3, 3, 0, 0, 3, 0, 2,
        0, 0, 0, 2, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 3, 3, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
    };
    int mod_2_chess[17][11]= // 初始化棋盘棋子属性 地图2
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 6, 0, 0, 0, 0, 0, 0, 0, 2, 4,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4,
        0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    for(int i = 0; i < 10; i++){
        enemygroup[i] = nullptr;
    }

    for(int i = 1; i <= 16; i++)
       for(int j = 1; j <= 10; j++)
       {
           pos[i][j] = new chess(this);
           pos[i][j]->setGeometry(58 * i - 58, 58 * j - 58, 60, 60);
           pos[i][j]->x = i;
           pos[i][j]->y = j;

           switch (mode) {
           case 1:
               if(mod_1_chess[i][j]>0&&mod_1_chess[i][j]<5){
                   total_plant++;
                   winlosscnt_plant++;
               }
                gamepos_init(pos[i][j], mod_1_chess[i][j], mod_1_map[i][j]);
                if(pos[i][j]->is_enemy)
                {
                    enemygroup[total_enemy] = pos[i][j];
                    total_enemy++;
                    winlosscnt_ene++;
                }
               break;
            case 2:
               if(mod_2_chess[i][j]>0 && mod_2_chess[i][j]<5){
                   total_plant++;
                   winlosscnt_plant++;
               }
               gamepos_init(pos[i][j], mod_2_chess[i][j], mod_2_map[i][j]);
               if(pos[i][j]->is_enemy)
               {
                   enemygroup[total_enemy] = pos[i][j];
                   total_enemy++;
                   winlosscnt_ene++;
               }
               break;
           default:
               break;
           }
           connect(pos[i][j], SIGNAL(clicked()), pos[i][j], SLOT(be_select())); //点击棋子会发送被选中的信号
           connect(pos[i][j], SIGNAL(crood(int, int)), this, SLOT(operate(int, int))); // gamemode可以接收到被选中的棋子的信号 进行后续操作
       }

}

void GameMode::operate(int x, int y) // 棋子的操作系统
{
    if(select==nullptr) // 如果主棋子(操作的棋子)为空
    {
        if(pos[x][y]->is_enemy || pos[x][y]->is_plant) // 如果当前棋子是敌人或者角色 在游戏界面显示棋子的角色或敌人属性
        {
            select = pos[x][y]; // 操作棋子定义

            if(select->is_plant)
            {
                ui->label_name->setText("NAME: "+ select->plant_name);
                ui->label_hp->setText("HP: " + QString::number(select->hp) + "/" + QString::number(select->MAX_HP));
                ui->label_sp->setText("SP: " + QString::number(select->sp));
                ui->label_atk->setText("ATK: " + QString::number(select->atk));
                ui->label_mag->setText("MAG: " + QString::number(select->mag));
            }
            else if(select->is_enemy)
            {
                ui->label_name->setText("NAME: "+ select->enemy_name);
                ui->label_hp->setText("HP: " + QString::number(select->hp) + "/" + QString::number(select->MAX_HP));
                ui->label_sp->clear();
                ui->label_atk->setText("ATK: " + QString::number(select->atk));
                ui->label_mag->clear();
            }

        }
    }
    else if(select != nullptr) // 如果已经有操作棋子了 那么再次传送过来的棋子坐标要么就是操作棋子本身 要么就是目标棋子
    {        
        if(select->x==x && select->y==y) // 再次点击已经被选中的操作的棋子 就是取消选中的意思 会清空和操作棋子相关的信息 并且释放操作棋子
        {
            actionfinish_clear(); // 取消显示范围
            select = nullptr; // 操作棋子为空
        }
        else // 在已经有操作棋子的情况下 如果第二次被点击的不是操作棋子 那么就只可能是亮起的chess.h（选择范围以内的棋子： 角色/ 敌人/ 空地）
        {
            if(select->is_enemy){
                ui->label_turn->setText("You can't control the enemy!");
                return;
            }
            if(!pos[x][y]->is_plant && !pos[x][y]->is_enemy && moving_d) //第二次点击的是空地 并且在移动模式 且操作棋子还没移动过 就可以进行移动
            {
                move_Animation(select, select->plant_name, select->x, select->y, x, y);

                int t_hp = select->hp;
                int t_sp = select->sp;

                gamepos_init(pos[x][y], select->plant_kind, pos[x][y]->pos_kind);

                pos[x][y]->hp = t_hp;
                pos[x][y]->sp = t_sp;
                if(pos[x][y]->pos_kind==2){
                    pos[x][y]->hp-=5;
                    if(pos[x][y]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                    {
                        ui->textBrowser->append(pos[x][y]->plant_name+"DIE!");
                        gamepos_init(pos[x][y], 0, pos[x][y]->pos_kind);
                        total_plant--;
                        winlosscnt_plant--;
                        checklosswin();
                    }
                    else // 如果血量不低于0 那就是还活着
                    {
                        pos[x][y]->hp -= 5; // 所以新血量就是临时血量的值
                    }
                }

                pos[x][y]->have_move = true;
                pos[x][y]->have_atk = select->have_atk;
                actionfinish_clear();

                int t_x = select->x;
                int t_y = select->y;
                int t_pos_kind = select->pos_kind;
                select->be_select(); // 取消选择这个棋子
                select = nullptr;

                gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                check_havedone(pos[x][y]);
            }

            else if(select->is_enemy!=pos[x][y]->is_enemy && select->is_plant != pos[x][y]->is_plant) // 操作棋子和目标棋子的阵营不一样只可以10 01配 不能和11和00和10配 00就是指空地面
            {
                if(!attack_d && !mag_d)
                    return;
                if(attack_d && select->atk>0 ) // 当前模式是攻击模式 因为操作和目标的阵营不一样 所以只可以是攻击 不可以是回血
                {
                    attack_Animation(pos[x][y], select->plant_name, pos[x][y]->enemy_name, x, y);

                    int t_hp = pos[x][y]->hp - select->atk; // t_hp是临时血量 是攻击的血量
                    if(t_hp <= 0) // 如果血量低于0 那就是死亡 并且判定那个棋子上已经不存在敌人或者角色
                    {
                        ui->textBrowser->append(pos[x][y]->enemy_name+"DIE!");
                        gamepos_init(pos[x][y], 0, pos[x][y]->pos_kind);
                        winlosscnt_ene--;
                        checklosswin();
                    }
                    else // 如果血量不低于0 那就是还活着
                    {
                        pos[x][y]->hp = t_hp; // 所以新血量就是临时血量的值
                    }
                }
                else if(mag_d && select->mag > 0 && select->sp > 0) // 当前模式是技能模式 因为操作和目标的阵营不一样 所以只可以是攻击 且要有sp才能放技能
                {
                    int t_hp = pos[x][y]->hp - select->mag; // t_hp是临时血量 是攻击的血量
                    attack_Animation(pos[x][y], select->plant_name, pos[x][y]->enemy_name, x, y);

                    if(t_hp <= 0) // 如果血量低于0 那就是死亡 并且判定那个棋子上已经不存在敌人
                    {
                        ui->textBrowser->append(pos[x][y]->enemy_name+"DIE!");
                        gamepos_init(pos[x][y], 0, pos[x][y]->pos_kind);
                        winlosscnt_ene--;
                        checklosswin();
                    }
                    else // 如果血量不低于0 那就是还活着
                    {
                        pos[x][y]->hp = t_hp; // 所以新血量就是临时血量的值
                    }
                    pos[select->x][select->y]->sp--;
                }

                actionfinish_clear(); // 取消显示范围 include chess_giveup_show()
                select->have_atk = true; // 这个棋子已经攻击的属性为真
                check_havedone(select); // 这个这个棋子的所有行动是否已经完成
                if(select!=nullptr)
                    select->be_select(); // 取消选择这个棋子
                select = nullptr; // 操作棋子为空
            }

            else if(select->is_enemy==pos[x][y]->is_enemy && select->is_plant == pos[x][y]->is_plant) // 操作棋子和目标棋子的阵营一样 治疗回血的
            {
                if(!attack_d && !mag_d)
                    return;
                if(attack_d && select->atk<0)
                {
                    ui->textBrowser->append(select->plant_name+" CURE "+pos[x][y]->plant_name);
                    curebgm->play();
                    curebgm->setLoops(1);

                    int t_hp = pos[x][y]->hp - select->atk; // t_hp是临时血量 是回血的血量
                    if(t_hp >= pos[x][y]->MAX_HP)
                        pos[x][y]->hp = pos[x][y]->MAX_HP;
                    else
                        pos[x][y]->hp = t_hp;
                }
                else if(mag_d && select->mag<0 && select->sp > 0)
                {
                    ui->textBrowser->append(select->plant_name+" CURE "+pos[x][y]->plant_name);
                    curebgm->play();
                    curebgm->setLoops(1);

                    int t_hp = pos[x][y]->hp - select->mag; // t_hp是临时血量 是回血的血量
                    if(t_hp >= pos[x][y]->MAX_HP)
                        pos[x][y]->hp = pos[x][y]->MAX_HP;
                    else
                        pos[x][y]->hp = t_hp;
                    pos[select->x][select->y]->sp--;
                }

                actionfinish_clear(); // 取消显示范围 include chess_giveup_show()
                select->have_atk = true; // 这个棋子已经移动的属性为真
                check_havedone(select); // 这个这个棋子的所有行动是否已经完成
                if(select!=nullptr)
                    select->be_select(); // 取消选择这个棋子
                select = nullptr; // 操作棋子为空
            }
        } 
    }
}

void GameMode::ai_operate()
{
    for(int i = 0; i < total_enemy; i++)
    {
        if(enemygroup[i]==nullptr || !enemygroup[i]->is_enemy){
            continue;
        }
        bool isBreakLoop = true; // 加判断标志跳出指定循环
        select = enemygroup[i];

        int ai_range_min_x = enemygroup[i]->x-enemygroup[i]->range;
        int ai_range_max_x = enemygroup[i]->x+enemygroup[i]->range;
        int ai_range_min_y = enemygroup[i]->y-enemygroup[i]->range;
        int ai_range_max_y = enemygroup[i]->y+enemygroup[i]->range;

        for(int j  = ai_range_min_x; j <= ai_range_max_x && isBreakLoop; j++){
            for(int k = ai_range_min_y; k <= ai_range_max_y && isBreakLoop; k++){
                if(j<1 || j>16 || k < 1 || k >10){
                    continue;
                }
                if(pos[j][k]->is_plant){ // 如果当前位置的攻击范围内有可攻击对象 那就先攻击再移动
                    attack_Animation(pos[j][k], select->enemy_name, pos[j][k]->plant_name, j, k);

                    int t_hp = pos[j][k]->hp - select->atk; // t_hp是临时血量 是攻击的血量
                    if(t_hp <= 0) // 如果血量低于0 那就是死亡 并且判定那个棋子上已经不存在敌人或者角色
                    {
                        ui->textBrowser->append(pos[j][k]->plant_name+"DIE!");
                        gamepos_init(pos[j][k], 0, pos[j][k]->pos_kind);
                        total_plant--;
                        winlosscnt_plant--;
                        checklosswin();
                    }
                    else // 如果血量不低于0 那就是还活着
                    {
                        pos[j][k]->hp = t_hp; // 所以新血量就是临时血量的值
                    }

                    isBreakLoop = false;
                    // enemy attack finish
                }
            }
        }
        isBreakLoop = true;

        int close_x = 0;
        int close_y = 0;
        int close_dis = 500;
        for(int j = 1; j <= 16; j++){
            for(int k = 1; k <= 10; k++){
                if(pos[j][k]->is_plant){
                    int dis = (select->x - j) * (select->x - j) + (select->y - k) * (select->y - k);
                    if(dis < close_dis){
                        close_dis = dis;
                        close_x = j;
                        close_y = k;
                    }
                }
            }
        }

        if(close_x > select->x && close_x - select->x-1 > 0){
            if(close_x - select->x >= select->speed){
//                qDebug()<<"move 1"<<endl;
                int t_speed = select->speed;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x+t_speed][select->y]->pos_kind==1 || pos[select->x+t_speed][select->y]->is_enemy || pos[select->x+t_speed][select->y]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x+t_speed, select->y);

                        gamepos_init(pos[select->x+t_speed][select->y], select->enemy_kind+5, pos[select->x+t_speed][select->y]->pos_kind);
                        pos[select->x+t_speed][select->y]->hp = t_hp;

                        if(pos[select->x+t_speed][select->y]->pos_kind == 2){
                            if(pos[select->x+t_speed][select->y]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x+t_speed][select->y]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x+t_speed][select->y], 0, pos[select->x+t_speed][select->y]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x-t_speed][select->y]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x+t_speed][select->y];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
            else
            {
//                qDebug()<<"move 2"<<endl;
                int t_speed = close_x - select->x - 1;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x+t_speed][select->y]->pos_kind==1 || pos[select->x+t_speed][select->y]->is_enemy || pos[select->x+t_speed][select->y]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x+t_speed, select->y);
                        gamepos_init(pos[select->x+t_speed][select->y], select->enemy_kind+5, pos[select->x+t_speed][select->y]->pos_kind);

                        pos[select->x+t_speed][select->y]->hp = t_hp;
                        if(pos[select->x+t_speed][select->y]->pos_kind == 2){
                            if(pos[select->x+t_speed][select->y]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x+t_speed][select->y]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x+t_speed][select->y], 0, pos[select->x+t_speed][select->y]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x+t_speed][select->y]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x+t_speed][select->y];

                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
        }
        else if(close_x < select->x && select->x - close_x-1 > 0)
        {
            if(select->x-close_x >= select->speed){
//                qDebug()<<"move 3";
                int t_speed = select->speed;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x-t_speed][select->y]->pos_kind==1 || pos[select->x-t_speed][select->y]->is_enemy || pos[select->x-t_speed][select->y]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x-t_speed, select->y);
                        gamepos_init(pos[select->x-t_speed][select->y], select->enemy_kind+5, pos[select->x-t_speed][select->y]->pos_kind);

                        pos[select->x-t_speed][select->y]->hp = t_hp;
                        if(pos[select->x-t_speed][select->y]->pos_kind == 2){
                            if(pos[select->x-t_speed][select->y]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x-t_speed][select->y]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x-t_speed][select->y], 0, pos[select->x-t_speed][select->y]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x-t_speed][select->y]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x-t_speed][select->y];

                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
            else
            {
//                qDebug()<<"move 4";
                int t_speed = select->x - close_x - 1;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x-t_speed][select->y]->pos_kind==1 || pos[select->x-t_speed][select->y]->is_enemy || pos[select->x-t_speed][select->y]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x-t_speed, select->y);
                        gamepos_init(pos[select->x-t_speed][select->y], select->enemy_kind+5, pos[select->x-t_speed][select->y]->pos_kind);

                        pos[select->x-t_speed][select->y]->hp = t_hp;
                        if(pos[select->x-t_speed][select->y]->pos_kind == 2){
                            if(pos[select->x-t_speed][select->y]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x-t_speed][select->y]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x-t_speed][select->y], 0, pos[select->x-t_speed][select->y]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x-t_speed][select->y]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x-t_speed][select->y];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
        }
        else if(close_y > select->y && close_x - select->y - 1 > 0){
            if(close_y-select->y >= select->speed){
                int t_speed = select->speed;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x][select->y+t_speed]->pos_kind==1 || pos[select->x][select->y+t_speed]->is_enemy || pos[select->x][select->y+t_speed]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x, select->y+t_speed);
                        gamepos_init(pos[select->x][select->y+t_speed], select->enemy_kind+5, pos[select->x][select->y+t_speed]->pos_kind);

                        pos[select->x][select->y+t_speed]->hp = t_hp;
                        if(pos[select->x][select->y+t_speed]->pos_kind == 2){
                            if(pos[select->x][select->y+t_speed]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x][select->y+t_speed]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x][select->y+t_speed], 0, pos[select->x][select->y+t_speed]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x][select->y+t_speed]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x][select->y+t_speed];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
            else
            {
//                qDebug()<<"move 6";
                int t_speed = close_y-select->y-1;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x][select->y+t_speed]->pos_kind==1 || pos[select->x][select->y+t_speed]->is_enemy || pos[select->x][select->y+t_speed]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x, select->y+t_speed);
                        gamepos_init(pos[select->x][select->y+t_speed], select->enemy_kind+5, pos[select->x][select->y+t_speed]->pos_kind);

                        pos[select->x][select->y+t_speed]->hp = t_hp;
                        if(pos[select->x][select->y+t_speed]->pos_kind == 2){
                            if(pos[select->x][select->y+t_speed]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x][select->y+t_speed]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x][select->y+t_speed], 0, pos[select->x][select->y+t_speed]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x][select->y+t_speed]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x][select->y+t_speed];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
        }
        else if(close_y < select->y && select->y  - close_y - 1 > 0)
        {
            if(select->y - close_y >= select->speed){
//                qDebug()<<"move 7";
                int t_speed = select->speed;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x][select->y-t_speed]->pos_kind==1 || pos[select->x][select->y-t_speed]->is_enemy || pos[select->x][select->y-t_speed]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x, select->y-t_speed);
                        gamepos_init(pos[select->x][select->y-t_speed], select->enemy_kind+5, pos[select->x][select->y-t_speed]->pos_kind);

                        pos[select->x][select->y-t_speed]->hp = t_hp;
                        if(pos[select->x][select->y-t_speed]->pos_kind == 2){
                            if(pos[select->x][select->y-t_speed]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x][select->y-t_speed]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x][select->y-t_speed], 0, pos[select->x][select->y-t_speed]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x][select->y-t_speed]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x][select->y-t_speed];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
            else
            {
//                qDebug()<<"move 8";
                int t_speed = select->y  - close_y - 1;
                if(select->pos_kind==3){
                    t_speed = 1;
                }
                while(t_speed>0){
                    if(pos[select->x][select->y-t_speed]->pos_kind==1 || pos[select->x][select->y-t_speed]->is_enemy || pos[select->x][select->y-t_speed]->is_plant){
                        t_speed--;
                    }
                    else{
                        int t_hp = select->hp;
                        move_Animation(select, select->enemy_name, select->x, select->y, select->x, select->y-t_speed);
                        gamepos_init(pos[select->x][select->y-t_speed], select->enemy_kind+5, pos[select->x][select->y-t_speed]->pos_kind);

                        pos[select->x][select->y-t_speed]->hp = t_hp;
                        if(pos[select->x][select->y-t_speed]->pos_kind == 2){
                            if(pos[select->x][select->y-t_speed]->hp-5 <= 0) // 如果血量低于0 那就是死亡
                            {
                                ui->textBrowser->append(pos[select->x][select->y-t_speed]->enemy_name+"DIE!");
                                gamepos_init(pos[select->x][select->y-t_speed], 0, pos[select->x][select->y-t_speed]->pos_kind);
                                winlosscnt_ene--;
                                checklosswin();
                            }
                            else // 如果血量不低于0 那就是还活着
                            {
                                pos[select->x][select->y-t_speed]->hp -= 5; // 所以新血量就是临时血量的值
                            }
                        }
                        enemygroup[i] = pos[select->x][select->y-t_speed];
                        int t_x = select->x;
                        int t_y = select->y;
                        int t_pos_kind = select->pos_kind;
                        select = nullptr;
                        gamepos_init(pos[t_x][t_y], 0, t_pos_kind);
                        break;
                    }
                }
            }
        }
        if(select!=nullptr)
            select = nullptr;
    }

    for(int i = 1; i <= 16; i++){ // 敌方开始行动 我方所有已行动和攻击状态清空
        for(int j = 1; j <= 10; j++){
            if(pos[i][j]->is_plant)
            {
                pos[i][j]->have_move = false;
                pos[i][j]->have_atk = false;
                pos[i][j]->lighted = false;
                pos[i][j]->selected = false;
            }
        }
    }
    round++;

    ui->textBrowser->append("Round "+ QString::number(round) +" Finish");
    ui->textBrowser->append("REMAIN ENEMY: " + QString::number(winlosscnt_ene));
    ui->textBrowser->append("REMAIN PLANT: " + QString::number(winlosscnt_plant));

    if(round == 1 && winlosscnt_ene==total_enemy){
        ui->textBrowser->append("ENEMY: Our power exceed your imagination! You're a dead man now!!!!");
    }
    if(round == 10){
        ui->textBrowser->append("DAVE: It's been so long, we're getting tired.");
    }
    if(winlosscnt_plant==total_plant/2){
        ui->textBrowser->append("DAVE: Half the plants are clear. What should we do?!");
    }
    if(winlosscnt_plant==1){
        ui->textBrowser->append("DAVE: It's our only hope...");
    }
    if(winlosscnt_ene==total_enemy/2){
        ui->textBrowser->append("DAVE: Come on! Victory in sight!");
    }
    if(winlosscnt_ene==1){
        ui->textBrowser->append("DAVE: Last odious monster!!!");
    }

}

void GameMode::on_pushButton_quit_clicked() //关闭游戏 这个函数有问题
{
    this->close();
}

void GameMode::on_pushButton_move_clicked() //选择移动模式
{
    if(select == nullptr || select->have_move || select->is_enemy)  // 如果操作棋子是空棋子 或者这个棋子已经移动过了 都不能选择移动模式
        return;

    if(!moving_d) // 如果当前不是移动模式
    {
        moving_d = true; // 开启移动模式 关闭技能和攻击模式
        attack_d = false;
        mag_d = false;
        chess_giveup_show();
        chess_move_show(); //显示可移动范围
    }
    else if(moving_d) // 如果当前已经是移动模式了 又选择移动模式 那就是要取消移动模式
    {
        moving_d = false; // 关闭移动模式
        chess_giveup_show(); // 放弃显示可移动范围
    }
}

void GameMode::chess_move_show()
{
    int t_speed;
    if(select->pos_kind == 3)
        t_speed = 1;
    else
        t_speed = select->speed;

    for(int a = 0; a <= t_speed; a++){
        for(int b = 0; b <= t_speed; b++){
            int t_x1 = select->x+a;
            int t_x2 = select->x-a;
            int t_y1 = select->y+b;
            int t_y2 = select->y-b;

            if((a==0 && b==0) || a+b>t_speed)
            {
            }
            else // 所有可移动的范围的棋子都会亮起 棋子的lighted属性为真
            {
                if(t_x1<17 && t_y1<11 && !pos[t_x1][t_y1]->is_enemy && !pos[t_x1][t_y1]->is_plant)
                {
                    pos[t_x1][t_y1]->be_light();
                }
                if(t_x1<17 && t_y2>0 && !pos[t_x1][t_y2]->is_enemy && !pos[t_x1][t_y2]->is_plant)
                {
                    pos[t_x1][t_y2]->be_light();
                }
                if(t_x2>0 && t_y1<11 && !pos[t_x2][t_y1]->is_enemy && !pos[t_x2][t_y1]->is_plant)
                {
                    pos[t_x2][t_y1]->be_light();
                }
                if(t_x2>0 && t_y2>0 && !pos[t_x2][t_y2]->is_enemy && !pos[t_x2][t_y2]->is_plant)
                {
                    pos[t_x2][t_y2]->be_light();
                }
            }
        }
    }
}

void GameMode::chess_giveup_show()  // 放弃显示可移动范围 但是会保留操作棋子
{
    for(int i = 1; i <= 16; i++){ // 遍历全图的棋子
        for(int j = 1; j <= 10; j++){
            if(pos[i][j]->lighted && pos[i][j] != select) // 如果棋子的lighted属性为真 且不是操作棋子就关闭lighted属性
            {
                pos[i][j]->not_be_light(); // 关闭lighted属性
            }
        }
    }
}

void GameMode::on_pushButton_atk_clicked() //点击即开启或者关闭攻击模式
{
    if(select == nullptr || select->have_atk || select->is_enemy)
        return;
    if(!attack_d) // 如果攻击模式未开启
    {
        if(select != nullptr) // 且有选中的棋子
        {
            attack_d = true; // 那就开启攻击模式 关闭其他模式
            moving_d = false;
            mag_d = false;
            chess_giveup_show();
            chess_atk_show();
        }
    }
    else if(attack_d) // 如果攻击模式已经开启 那再次点击就是要关闭攻击模式
    {
        attack_d = false; // 关闭攻击模式
        chess_giveup_show(); // 取消显示攻击范围
    }
}

void GameMode::chess_atk_show()
{
    int t_range = select->range;
    // 攻击范围以内的棋子亮起 lighted属性为真
    switch(t_range)
    {
    case 1:
    case 2:
    case 3:
        for(int a = 1; a <= t_range; a++){
            if(select->y+a<11){
                pos[select->x][select->y+a]->be_light();
            }
            if(select->y-a>0){
                pos[select->x][select->y-a]->be_light();
            }
            if(select->x+a<17){
                pos[select->x+a][select->y]->be_light();
            }
            if(select->x-a>0){
                pos[select->x-a][select->y]->be_light();
            }
        }
        break;
    case 4:
        int a = 1;
        if(select->y+a<11){
            pos[select->x][select->y+a]->be_light();
            if(select->x+a<17){
                pos[select->x+a][select->y+a]->be_light();
            }
            if(select->x-a>0){
                pos[select->x-a][select->y+a]->be_light();
            }
        }
        if(select->y-a>0){
            pos[select->x][select->y-a]->be_light();
            if(select->x+a<17){
                pos[select->x+a][select->y-a]->be_light();
            }
            if(select->x-a>0){
                pos[select->x-a][select->y-a]->be_light();
            }
        }
        if(select->x+a<17){
            pos[select->x+a][select->y]->be_light();
        }
        if(select->x-a>0){
            pos[select->x-a][select->y]->be_light();
        }
        break;
    }
}

void GameMode::on_pushButton_mag_clicked() // 点击开启或关闭技能模式
{
    if(select == nullptr || select->have_atk || select->is_enemy)
        return;
    if(!mag_d)
    {
        if(select != nullptr)
        {
            mag_d = true;
            attack_d = false;
            moving_d = false;
//            qDebug() << "this chess is going to mag" ;
            chess_giveup_show();
            chess_atk_show(); // 技能模式的攻击范围和攻击模式是一样的
        }
    }
    else if(mag_d)
    {
//        qDebug() << "this chess gives up attack" ;
        mag_d = false;
        chess_giveup_show();
    }
}

void GameMode::on_pushButton_skip_clicked()
{
    if(select != nullptr)
    {
        if(select->have_atk && select->have_move)
        {
            return;
        }
        actionfinish_clear(); // 取消显示范围 include chess_giveup_show()
        select->have_atk = true; // 这个棋子已经攻击的属性为真
        select->have_move = true; // 这个棋子已经移动的属性为真
        check_havedone(select); // 这个这个棋子的所有行动是否已经完成
        if(select!=nullptr)
            select->be_select(); // 取消选择这个棋子
//        qDebug()<<"check skip finish"<<endl;
        select = nullptr; // 操作棋子为空
    }
}

void GameMode::actionfinish_clear()
{
    ui->label_name->clear();
    ui->label_hp->clear();
    ui->label_sp->clear();
    ui->label_atk->clear();
    ui->label_mag->clear();

    chess_giveup_show();
    moving_d = false;
    attack_d = false;
    mag_d = false;
}

void GameMode::check_havedone(chess *tmp)
{
    if(select==nullptr){
    }
    if(tmp->have_move && tmp->have_atk)
    {
        count_move++;
        if(count_move == total_plant)
        {
            if(select==nullptr){
            }
            if(select!=nullptr){
                select->be_select();
            }
            select = nullptr;
            count_move = 0;
            ai_operate();
        }
    }
}

void GameMode::gamepos_init(chess *tmp, int chess_kind, int map_kind)
{
    switch(chess_kind) // 这个switch是定义棋子上的角色或者敌人属性 太阳花是奶妈是负数
    {
    case 0:
        tmp->is_plant = false;
        tmp->plant_kind = 0;
        tmp->is_enemy = false;
        tmp->enemy_kind = 0;
        tmp->hp = 0;
        tmp->MAX_HP = 0;
        tmp->sp = 0;
        tmp->atk = 0;
        tmp->mag = 0;
        tmp->range = 0;
        tmp->speed = 0;
        break;

     case 1:
        tmp->is_plant = true;
        tmp->plant_kind = 1;
        tmp->plant_name = "Chomper";
        tmp->is_enemy = false;
        tmp->hp = 100;
        tmp->MAX_HP = 100;
        tmp->sp = 3;
        tmp->atk = 20;
        tmp->mag = 25;
        tmp->range = 2;
        tmp->speed = 3;
        break;

     case 2:
        tmp->is_plant = true;
        tmp->plant_kind = 2;
        tmp->plant_name = "NutWall";
        tmp->is_enemy = false;
        tmp->hp = 150;
        tmp->MAX_HP = 150;
        tmp->sp = 3;
        tmp->atk = 15;
        tmp->mag = 20;
        tmp->range = 1;
        tmp->speed = 2;
        break;

     case 3:
        tmp->is_plant = true;
        tmp->plant_kind = 3;
        tmp->plant_name = "Sunflower";
        tmp->is_enemy = false;
        tmp->hp = 75;
        tmp->MAX_HP = 75;
        tmp->atk = -10;
        tmp->sp = 3;
        tmp->mag = - 15;
        tmp->range = 4;
        tmp->speed = 2;
        break;

    case 4:
        tmp->is_plant = true;
        tmp->plant_kind = 4;
        tmp->plant_name = "FumeShroom";
        tmp->is_enemy = false;
        tmp->hp = 90;
        tmp->MAX_HP = 90;
        tmp->atk = 15;
        tmp->sp = 3;
        tmp->mag = 25;
        tmp->range = 3;
        tmp->speed = 2;
        break;

    case 5:
        break;

    case 6:
        tmp->is_enemy = true;
        tmp->enemy_kind = 1;
        tmp->enemy_name = "Rider";
        tmp->is_plant = false;
        tmp->hp = 100;
        tmp->MAX_HP = 100;
        tmp->atk = 20;
        tmp->range = 2;
        tmp->speed = 3;
        break;
    case 7:
        tmp->is_enemy = true;
        tmp->enemy_kind = 2;
        tmp->enemy_name = "Rock";
        tmp->is_plant = false;
        tmp->hp = 150;
        tmp->MAX_HP = 150;
        tmp->atk = 10;
        tmp->range = 1;
        tmp->speed = 2;
        break;

     case 8:
        tmp->is_enemy = true;
        tmp->enemy_kind = 3;
        tmp->enemy_name = "Spray";
        tmp->is_plant = false;
        tmp->hp = 90;
        tmp->MAX_HP = 90;
        tmp->atk = 15;
        tmp->range = 3;
        tmp->speed = 2;
        break;

    case 9:
        tmp->is_enemy = true;
        tmp->enemy_kind = 4;
        tmp->enemy_name = "boss";
        tmp->is_plant = false;
        tmp->hp = 300;
        tmp->MAX_HP = 300;
        tmp->atk = 35;
        tmp->sp = 1;
        tmp->mag = 50;
        tmp->range = 1;
        tmp->speed = 1;
        break;

    default:
        break;
    }

    tmp->selected = false; //单个棋子有没有被选中
    tmp->lighted = false; //棋子有没有亮起
    tmp->have_atk = false;
    tmp->have_move = false;

    tmp->pos_kind = map_kind; // 地形初始化
    tmp->pos_init(); // 地图初始化 基本贴图
    tmp->show();
}

void GameMode::checklosswin()
{
    if(winlosscnt_ene==0 || winlosscnt_plant==0)
    {
        gamemodebgm->stop();
        QString winloss;
        if(winlosscnt_ene==0){
            QSound *winmusic = new QSound(":/bgm/bgm/winmusic.wav", this);
            winmusic->play();
            winmusic->setLoops(1);
            winloss = "YOU WIN!!!";
        }
        else if(winlosscnt_plant==0){
            QSound *lossmusic = new QSound(":/bgm/bgm/losemusic.wav", this);
            lossmusic->play();
            lossmusic->setLoops(1);
            winloss = "YOU LOSS!!!";
        }
        QMessageBox messageBox(QMessageBox::NoIcon, "RESULT", winloss, QMessageBox::Ok, NULL);
        messageBox.setWindowFlag(Qt::WindowStaysOnTopHint);
        int result = messageBox.exec();
        switch(result)
        {
        case QMessageBox::Ok :
//            qDebug()<<"OK";
            this->close();
        }
        this->close();
    }
}



void GameMode::on_pushButton_check_clicked()
{
    for(int i = 1; i <= 16; i++){
        for(int j = 1; j <= 10; j++){
            if(pos[i][j]->is_plant){
                if(!pos[i][j]->have_atk){
                    ui->textBrowser->append(QString::number(i)+" "+QString::number(j)+" "+pos[i][j]->plant_name+" hasn't attacked");
                }
                if(!pos[i][j]->have_move){
                    ui->textBrowser->append(QString::number(i)+" "+QString::number(j)+" "+pos[i][j]->plant_name+" hasn't moved");
                }
            }
        }
    }
}

void GameMode::on_pushButton_finish_clicked()
{
    if(select!=nullptr){
        select->be_select();
    }
    select = nullptr;
    count_move=0;
    ai_operate();
}

void GameMode::move_Animation(chess *tmp, QString tmp_name, int start_x, int start_y, int end_x, int end_y)
{
   ui->textBrowser->append(tmp_name + " Start moving");

   QString ground[4] = {"road", "block", "spines", "swamp"};
   QString path = ":/map/icons/map/" + tmp_name + "/" +ground[tmp->pos_kind] + "_" + tmp_name + "0_move.png";
   QPushButton *aniMove = new QPushButton(this);
   QIcon icon(path);
   aniMove->setIcon(icon);
   aniMove->setIconSize(QSize(60, 60));
   aniMove->setGeometry(58 * start_x - 58, 58 * start_y - 58, 60, 60);
   aniMove->show();
   aniMove->raise();
   QPropertyAnimation *animation = new QPropertyAnimation(aniMove, "pos");
   animation->setStartValue(QPoint(58 * start_x - 58, 58 * start_y - 58));
   animation->setEndValue(QPoint(58 * end_x, 58 * end_y));
   animation->setEasingCurve(QEasingCurve::Linear);
   animation->setDuration(300);
   animation->start(QAbstractAnimation::DeleteWhenStopped);

   QTime p;
   p.start();
   while(p.elapsed()<300){
       QCoreApplication::processEvents();
   }

   delete aniMove;
}

void GameMode::attack_Animation(chess *pas, QString act_name, QString pas_name, int tmp_x, int tmp_y)
{
    ui->textBrowser->append(act_name+" ATTACK "+ pas_name);

    QString ground[4] = {"road", "block", "spines", "swamp"};
    QString path = ":/map/icons/map/"+pas_name +"/"+ground[pas->pos_kind]+"_"+ pas_name +"0_ATK.png";
    QPushButton *aniAttack = new QPushButton(this);
    QIcon Icon(path);
    aniAttack->setIcon(Icon);
    aniAttack->setIconSize(QSize(60, 60));
    aniAttack->setGeometry(58 * tmp_x - 58, 58 * tmp_y - 58, 60, 60);
    aniAttack->show();
    aniAttack->raise();
    attackbgm->play();
    attackbgm->setLoops(1);

    QTime p;
    p.start();
    while(p.elapsed()<300){
        QCoreApplication::processEvents();
    }

    delete aniAttack;
}



















