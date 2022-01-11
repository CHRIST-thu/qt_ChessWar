#ifndef METHODDIALOG_H
#define METHODDIALOG_H

#include <QDialog>

namespace Ui {
class MethodDialog;
}

class MethodDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MethodDialog(QWidget *parent = nullptr);
    ~MethodDialog();

private:
    Ui::MethodDialog *ui;
};

#endif // METHODDIALOG_H
