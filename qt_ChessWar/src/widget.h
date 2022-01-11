#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QSound>
#include "gamestart_dialog.h"
#include "methoddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void closeEvent( QCloseEvent * event );
private slots:

    void on_Start_Button_clicked();

    void show_widget();

    void on_Method_Button_clicked();

private:
    Ui::Widget *ui;
    Gamestart_Dialog *gamestart_dialog;
    MethodDialog *method_dialog;
    QSound *widgetbgm = new QSound(":/bgm/bgm/widgetmusic.wav", this);
};
#endif // WIDGET_H
