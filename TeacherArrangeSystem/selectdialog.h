#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();
    QString GetValue();
    //int GetInt();
    int m_iRadioID; //当前选中的是哪个，0--高于，1--等于，2--低于
    int m_iSelectIndex;
    void on_comboBox_currentIndexChanged(int index);
    //QDate GetDate();
private slots:
    void on_radioButtonHigher_clicked();

    void on_radioButtonEqual_clicked();

    void on_radioButtonLower_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
