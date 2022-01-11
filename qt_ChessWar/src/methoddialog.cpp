#include "methoddialog.h"
#include "ui_methoddialog.h"
#include <QLabel>
#include <QPixmap>

MethodDialog::MethodDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("HOW TO PLAY");
    QString spath = ":/map/icons/select2.png";
    QPixmap picPixmap;
    picPixmap.load(spath);
    QPixmap TempPixmap = picPixmap.scaled(ui->label->width(), ui->label->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(TempPixmap);
}

MethodDialog::~MethodDialog()
{
    delete ui;
}
