#ifndef ADDTEACHERDIALOG_H
#define ADDTEACHERDIALOG_H

#include <QDialog>

namespace Ui {
class AddTeacherDialog;
}

class AddTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeacherDialog(QWidget *parent = nullptr);
    ~AddTeacherDialog();
    QString Name();
    int Id();
    QString Sex();
    QDate BirthDate();
    QString Rank();
    QString Degree();
    double Salary();
    QString IsMarried();
private:
    Ui::AddTeacherDialog *ui;
};

#endif // ADDTEACHERDIALOG_H
