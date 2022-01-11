#include "gamestart_dialog.h"
#include "ui_gamestart_dialog.h"
#include "gamemode.h"
#include "widget.h"
#include <QWidget>
#include <QDebug>

Gamestart_Dialog::Gamestart_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamestart_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("CHOOSE MODE");
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    gamemode = new GameMode;
}

Gamestart_Dialog::~Gamestart_Dialog()
{
    delete ui;
}

void Gamestart_Dialog::on_mode_1_button_clicked()
{
    gamemode->mode = 1;
    emit gamemode->init_map();
    gamemode->setWindowFlag(Qt::WindowStaysOnTopHint);//让mode_1出现 并且置顶
    gamemode->show();
    this->close(); //关闭gamestart_dialog视窗
}



void Gamestart_Dialog::on_mode_2_button_clicked()
{
    gamemode->mode = 2;
    emit gamemode->init_map();
    gamemode->setWindowFlag(Qt::WindowStaysOnTopHint);//让mode_2出现 并且置顶
    gamemode->show();
    this->close(); //关闭gamestart_dialog视窗
}
