#ifndef ADDLESSONDIALOG_H
#define ADDLESSONDIALOG_H

#include <QDialog>
#include "ui_addlessondialog.h"

class AddLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLessonDialog(QWidget *parent = nullptr);
    ~AddLessonDialog();

    QString LessonName();
    int LessonID();
    double ClassHours();
    QString Classroom();
    QString TeachingClass();
    double Credits();
    QString Semester();
    int TeacherID();

private:
    Ui::AddLessonDialog *ui;
};

#endif // ADDLESSONDIALOG_H
