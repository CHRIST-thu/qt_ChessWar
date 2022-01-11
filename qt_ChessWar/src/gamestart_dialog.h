#ifndef GAMESTART_DIALOG_H
#define GAMESTART_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include "gamemode.h"
#include <QDebug>

namespace Ui {
class Gamestart_Dialog;
}

class Gamestart_Dialog : public QDialog
{
    Q_OBJECT

public:
    GameMode *gamemode;
    explicit Gamestart_Dialog(QWidget *parent = nullptr);
    ~Gamestart_Dialog();


private slots:
    void on_mode_1_button_clicked();
    void on_mode_2_button_clicked();

private:
    Ui::Gamestart_Dialog *ui;

};

#endif // GAMESTART_DIALOG_H
