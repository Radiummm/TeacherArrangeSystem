#ifndef ENTERTEACHERIDDIALOG_H
#define ENTERTEACHERIDDIALOG_H

#include <QDialog>

namespace Ui {
class EnterTeacherIdDialog;
}

class EnterTeacherIdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnterTeacherIdDialog(QWidget *parent = nullptr);
    ~EnterTeacherIdDialog();
    int Number();
private:
    Ui::EnterTeacherIdDialog *ui;
};

#endif // ENTERTEACHERIDDIALOG_H
