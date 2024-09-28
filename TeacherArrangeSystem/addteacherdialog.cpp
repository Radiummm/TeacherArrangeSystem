#include "addteacherdialog.h"
#include "ui_addteacherdialog.h"
#include<QDebug>
AddTeacherDialog::AddTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeacherDialog)
{
    ui->setupUi(this);
}

AddTeacherDialog::~AddTeacherDialog()
{
    delete ui;
}
QString AddTeacherDialog::Name()
{
    return ui->textEditName->toPlainText();
}
int AddTeacherDialog::Id()
{
    QString sNumber = ui->textEditTeacherId->toPlainText();
    int number = sNumber.toInt();
    return number;
}
QString AddTeacherDialog::Sex()
{
    QString sex = ui->textEditSex->toPlainText();
    return sex;
}
QDate AddTeacherDialog::BirthDate()
{
    return ui->dateEditBirthday->date();
}
QString AddTeacherDialog::Rank()
{
    return ui->textEditRank->toPlainText();
}
QString AddTeacherDialog::Degree()
{
    return ui->textEditDegree->toPlainText();
}
double AddTeacherDialog::Salary()
{
    QString m_salary = ui->textEditSalary->toPlainText();
      float salary = m_salary.toFloat();
      //qDebug()<<salary;
      return salary;

}
QString AddTeacherDialog::IsMarried()
{
    //qDebug()<<ui->textEditIsMarried->toPlainText();
    return ui->textEditIsMarried->toPlainText();
}
