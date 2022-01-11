#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDialog>
#include <QSound>
#include "gamestart_dialog.h"
#include "methoddialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("PLANT VS ISSAC");
    widgetbgm->play();
    widgetbgm->setLoops(-1);

//点击退出键退出游戏
//TODO: 提醒用户是否确认关闭游戏
    QObject::connect(ui->Quit_Button, SIGNAL(clicked()), qApp, SLOT(quit()));

}

//https://www.cnblogs.com/ybqjymy/p/12654391.html 提示用户是否确定关闭窗口
void Widget::closeEvent( QCloseEvent * event ){
    widgetbgm->stop();
    switch( QMessageBox::information( this, tr("Control View"),
                                      tr("Do you really want to quit PVZChessWar?"),
                                      tr("Yes"), tr("No"), 0, 1 ) )
    {
    case 0:
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::show_widget()
{
    this->show();
    widgetbgm->play();
    widgetbgm->setLoops(-1);
}

void Widget::on_Start_Button_clicked()
{
    widgetbgm->stop();
    gamestart_dialog = new Gamestart_Dialog(this);
    connect(gamestart_dialog->gamemode, SIGNAL(show_main()), this, SLOT(show_widget()));
    gamestart_dialog->exec();
    this->hide();
}

void Widget::on_Method_Button_clicked()
{
    method_dialog = new MethodDialog(this);
    method_dialog->exec();
}
