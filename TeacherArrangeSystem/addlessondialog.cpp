#include "addlessondialog.h"
#include "ui_addlessondialog.h"

AddLessonDialog::AddLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLessonDialog)
{
    ui->setupUi(this);
}

AddLessonDialog::~AddLessonDialog()
{
    delete ui;
}

QString AddLessonDialog::LessonName()
{
    return ui->textEditLessonName->toPlainText();
}

int AddLessonDialog::LessonID()
{
    QString sID = ui->textEditLessonId->toPlainText();
    int id = sID.toInt();
    return id;
}

double AddLessonDialog::ClassHours()
{
    QString sHours = ui->textEditLastTime->toPlainText();
    double hours = sHours.toDouble();
    return hours;
}

QString AddLessonDialog::Classroom()
{
    return ui->textEditClassroom->toPlainText();
}

QString AddLessonDialog::TeachingClass()
{
    return ui->textEditClassGroup->toPlainText();
}

double AddLessonDialog::Credits()
{
    QString sCredits = ui->textEditGpa->toPlainText();
    double credits = sCredits.toDouble();
    return credits;
}

QString AddLessonDialog::Semester()
{
    return ui->textEditSemester->toPlainText();
}

int AddLessonDialog::TeacherID()
{
    QString sTeacherID = ui->textEditTeacherId->toPlainText();
    int teacherID = sTeacherID.toInt();
    return teacherID;
}
