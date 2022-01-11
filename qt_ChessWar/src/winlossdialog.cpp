#include "winlossdialog.h"
#include "ui_winlossdialog.h"

WinLossDialog::WinLossDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinLossDialog)
{
    ui->setupUi(this);
}

WinLossDialog::~WinLossDialog()
{
    delete ui;
}
