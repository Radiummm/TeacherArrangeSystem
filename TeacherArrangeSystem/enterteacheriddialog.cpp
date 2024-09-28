#include "enterteacheriddialog.h"
#include "ui_enterteacheriddialog.h"

EnterTeacherIdDialog::EnterTeacherIdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterTeacherIdDialog)
{
    ui->setupUi(this);
}

EnterTeacherIdDialog::~EnterTeacherIdDialog()
{
    delete ui;
}
int EnterTeacherIdDialog::Number()
{
    QString sNumber = ui->textEditTeacherID->toPlainText();
     int number = sNumber.toInt();
     return number;

}
