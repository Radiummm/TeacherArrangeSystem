#include "selectdialog.h"
#include "ui_selectdialog.h"
#include<QDate>
#include<QDebug>
SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    ui->radioButtonHigher->setChecked(true);
      m_iRadioID = 0;
      m_iSelectIndex = 0;
      ui->label_unit->setText("元");
      connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SelectDialog::on_comboBox_currentIndexChanged);

}

SelectDialog::~SelectDialog()
{
    delete ui;
}
QString SelectDialog::GetValue()
{
    return ui->lineEdit->text();
}

//int SelectDialog::GetInt()
//{
//    QString strValue = ui->lineEdit->text();
//    int Value = strValue.toInt();
//    return Value;
//}
//QDate SelectDialog::GetDate()
//{
//    QString dateStr = ui->lineEdit->text();
//    QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
//    return date;
//}

void SelectDialog::on_radioButtonHigher_clicked()
{
    m_iRadioID = 0;

}

void SelectDialog::on_radioButtonEqual_clicked()
{
    m_iRadioID = 1;

}

void SelectDialog::on_radioButtonLower_clicked()
{
    m_iRadioID = 2;

}
void SelectDialog::on_comboBox_currentIndexChanged(int index)
{   qDebug()<<index;
    if(index == 0)
    {
        m_iSelectIndex = 0;
        ui->label_unit->setText("元");

    }

    if(index == 1)
    {
        m_iSelectIndex = 1;
        ui->label_unit->setText(" ");
    }
    if(index == 2)
    {
        m_iSelectIndex = 2;
        ui->label_unit->setText(" ");
    }
}

