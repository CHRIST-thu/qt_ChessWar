#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QWidget>
#include <QSound>
#include "chess.h"

namespace Ui {
class GameMode;
}

class GameMode : public QWidget
{
    Q_OBJECT

public:
    explicit GameMode(QWidget *parent = nullptr);
    ~GameMode();
    void closeEvent( QCloseEvent * event );

    chess* pos[17][11];
    chess *select = nullptr;
    chess *enemygroup[10];

    int mode;
    bool moving_d  =  false;
    void chess_move_show();

    bool mag_d = false;
    bool attack_d = false;
    void chess_atk_show();
    void chess_giveup_show();

    int count_move = 0;
    int total_plant = 0;
    int total_enemy = 0;
    int winlosscnt_plant = 0;
    int winlosscnt_ene = 0;

    void actionfinish_clear();
    void check_havedone(chess *tmp);
    void gamepos_init(chess *tmp, int chess_kind, int map_kind);

    int round = 0;
    void checklosswin();

    void move_Animation(chess *tmp, QString tmp_name, int start_x, int start_y, int end_x, int end_y);
    void attack_Animation(chess *pas, QString act_name, QString pas_name, int tmp_x, int tmp_y);

public slots:
    void operate(int, int);
    void init_map();
    void ai_operate();

private:
    Ui::GameMode *ui;

signals:
    void show_main();

private slots:

    void on_pushButton_quit_clicked();
    void on_pushButton_move_clicked();
    void on_pushButton_atk_clicked();
    void on_pushButton_mag_clicked();
    void on_pushButton_skip_clicked();
    void on_pushButton_check_clicked();
    void on_pushButton_finish_clicked();

private:
    QSound *gamemodebgm = new QSound(":/bgm/bgm/gamemodemusic.wav", this);
    QSound *attackbgm = new QSound(":/bgm/bgm/attackmusic.wav", this);
    QSound *curebgm = new QSound(":/bgm/bgm/curemusic.wav", this);

};

#endif // GAMEMODE_H
