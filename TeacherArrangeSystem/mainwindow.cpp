#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"addteacherdialog.h"
#include"teacher.h"
#include"readonlydelegate.h"
#include<QDir>
#include<QString>
#include<QDate>
#include<QFileDialog>
#include"selectdialog.h"
#include"addlessondialog.h"
#include"enterteacheriddialog.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ShowInfotableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ShowInfotableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->ShowInfotableView->setModel(teacherInfoModel);
    connect(ui->ShowInfotableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::on_ShowInfotableView_changed);
    ui->ShowInfotableView->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单
    RightClickMenu = new QMenu();               //右键点击菜单
    deleteAction = new QAction("删除",this);     //单行删除事件
    RightClickMenu->addAction(deleteAction);    //将action添加到菜单内
    connect(ui->ShowInfotableView,&QTableView::customContextMenuRequested,this,&MainWindow::onGetMousePos);
    connect(RightClickMenu,&QMenu::triggered,this,&MainWindow::onMenuAction);


}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //窗口改变大小的时候列表控件跟着改变
    ui->ShowInfotableView->setGeometry(5,5,x*0.99,y*0.99);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowTeacherInfoTable()
{   //qDebug()<<111;
    //qDebug()<<teacherInfoModel;
    m_iCurTable=TeacherInfo;

        teacherInfoModel = new QStandardItemModel(this);
        ui->ShowInfotableView->setModel(teacherInfoModel);
        teacherInfoModel->setColumnCount(8);

        QStringList headerLabels;
        headerLabels << "编号" << "姓名" << "性别" << "出生年月" << "职称" << "最后学历" << "工资" << "婚否";
        teacherInfoModel->setHorizontalHeaderLabels(headerLabels);


    QList<Teacher> teachers = m_TeacherManager.getAllTeachers();

    teacherInfoModel->setRowCount(teachers.size());

    for (int i = 0; i < teachers.size(); ++i) {
        teacherInfoModel->setItem(i, 0, new QStandardItem(QString::number(teachers[i].ID)));
        teacherInfoModel->setItem(i, 1, new QStandardItem(teachers[i].name));
        teacherInfoModel->setItem(i, 2, new QStandardItem(teachers[i].sex));
        teacherInfoModel->setItem(i, 3, new QStandardItem(teachers[i].birth.toString("yyyy-MM-dd")));
        teacherInfoModel->setItem(i, 4, new QStandardItem(teachers[i].rank));
        teacherInfoModel->setItem(i, 5, new QStandardItem(teachers[i].degree));
        teacherInfoModel->setItem(i, 6, new QStandardItem(QString::number(teachers[i].salary)));
        teacherInfoModel->setItem(i, 7, new QStandardItem(teachers[i].isMarried));
    }
}

//void MainWindow::ShowLessonInfoTable(int id)
//{
//    QStandardItemModel *lessonModel = new QStandardItemModel();
//    lessonModel->setColumnCount(7);
//    m_iCurTable=TeacherLessonInfo;
//    QStringList headerLabels;
//    headerLabels << "课程编号" << "课程名称" << "课时" << "教室" << "授课班级" << "学分" << "学期";
//    lessonModel->setHorizontalHeaderLabels(headerLabels);

//    QList<Lesson> lessons = m_TeacherManager.FIndTeacherById(id)->lessons;



//    QList<Lesson> lessonstest = m_LessonManager.getAllLesson();
//    //qDebug() << "Total Lessons:" << lessonstest.size();



//    int rowCount = lessons.size();
//    lessonModel->setRowCount(rowCount);

//    for (int i = 0; i < rowCount; ++i)
//    {
//        QString tempStr;
//        QStandardItem *item;

//        tempStr = QString::number(lessons[i].lessonID);
//        item = new QStandardItem(tempStr);
//        lessonModel->setItem(i, 0, item);

//        item = new QStandardItem(lessons[i].lessonName);
//        lessonModel->setItem(i, 1, item);

//        tempStr = QString::number(lessons[i].lastTime);
//        item = new QStandardItem(tempStr);
//        lessonModel->setItem(i, 2, item);

//        item = new QStandardItem(lessons[i].classroom);
//        lessonModel->setItem(i, 3, item);

//        item = new QStandardItem(lessons[i].classGroup);
//        lessonModel->setItem(i, 4, item);

//        tempStr = QString::number(lessons[i].gpa);
//        item = new QStandardItem(tempStr);
//        lessonModel->setItem(i, 5, item);

//        item = new QStandardItem(lessons[i].semester);
//        lessonModel->setItem(i, 6, item);
//    }

//    ui->ShowInfotableView->setModel(lessonModel);

//}

//void MainWindow::ShowTeacherDetailTable(int teacherId)//用于advancedSearch
//{
//    QStandardItemModel *teacherDetailModel = new QStandardItemModel();
//    teacherDetailModel->setColumnCount(9);

//    QStringList headerLabels;
//    headerLabels << "编号" << "姓名" << "性别" << "出生年月" << "职称" << "最后学历" << "工资" << "婚否" << "授课信息";
//    teacherDetailModel->setHorizontalHeaderLabels(headerLabels);

//    Teacher* teacher = m_TeacherManager.FIndTeacherById(teacherId);

//
//    teacherDetailModel->setRowCount(1);

//    QString tempStr;
//    QStandardItem *item;

//    tempStr = QString::number(teacher->ID);
//    item = new QStandardItem(tempStr);
//    teacherDetailModel->setItem(0, 0, item);

//    item = new QStandardItem(teacher->name);
//    teacherDetailModel->setItem(0, 1, item);

//    item = new QStandardItem(teacher->sex);
//    teacherDetailModel->setItem(0, 2, item);

//    tempStr = teacher->birth.toString("yyyy-MM-dd");
//    item = new QStandardItem(tempStr);
//    teacherDetailModel->setItem(0, 3, item);

//    item = new QStandardItem(teacher->rank);
//    teacherDetailModel->setItem(0, 4, item);

//    item = new QStandardItem(teacher->degree);
//    teacherDetailModel->setItem(0, 5, item);

//    tempStr = QString::number(teacher->salary);
//    item = new QStandardItem(tempStr);
//    teacherDetailModel->setItem(0, 6, item);

//    item = new QStandardItem(teacher->isMarried);
//    teacherDetailModel->setItem(0, 7, item);

//    QString lessonInfo;
//    foreach (const Lesson &lesson, teacher->lessons) {
//        lessonInfo += QString("课程编号: %1, 课程名称: %2\n")
//                          .arg(lesson.lessonID)
//                          .arg(lesson.lessonName);
//    }
//    item = new QStandardItem(lessonInfo);
//    teacherDetailModel->setItem(0, 8, item);

//    ui->ShowInfotableView->setModel(teacherDetailModel);
//    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
//    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
//}
void MainWindow::ShowTeacherLessonInfoTable(int teacherId)
{
    m_iCurTable=TeacherLessonInfo;
      //qDebug()<<lessonInfoModel;

        lessonInfoModel = new QStandardItemModel(this);
        ui->ShowInfotableView->setModel(lessonInfoModel);
        lessonInfoModel->setColumnCount(7);

        QStringList headerLabels;
        headerLabels << "课程编号" << "课程名称" << "课时" << "教室" << "授课班级" << "学分" << "学期";
        lessonInfoModel->setHorizontalHeaderLabels(headerLabels);

    QList<Lesson> lessons = m_TeacherManager.FIndTeacherById(teacherId)->lessons;

        int rowCount = lessons.size();
        lessonInfoModel->setRowCount(rowCount);

        for (int i = 0; i < rowCount; ++i)
        {
            QString tempStr;
            QStandardItem *item;

            tempStr = QString::number(lessons[i].lessonID);
            item = new QStandardItem(tempStr);
            lessonInfoModel->setItem(i, 0, item);

            item = new QStandardItem(lessons[i].lessonName);
            lessonInfoModel->setItem(i, 1, item);

            tempStr = QString::number(lessons[i].lastTime);
            item = new QStandardItem(tempStr);
            lessonInfoModel->setItem(i, 2, item);

            item = new QStandardItem(lessons[i].classroom);
            lessonInfoModel->setItem(i, 3, item);

            item = new QStandardItem(lessons[i].classGroup);
            lessonInfoModel->setItem(i, 4, item);

            tempStr = QString::number(lessons[i].gpa);
            item = new QStandardItem(tempStr);
            lessonInfoModel->setItem(i, 5, item);

            item = new QStandardItem(lessons[i].semester);
            lessonInfoModel->setItem(i, 6, item);
        }
    }


void MainWindow::on_actionDeleteTeacher_triggered()
{

}

void MainWindow::on_actionAddLesson_triggered()
{
    AddLessonDialog dlgLesson(this);
       int ret = dlgLesson.exec();

       if (ret == QDialog::Accepted)
       {
           Lesson tempLesson;
           tempLesson.lessonName = dlgLesson.LessonName();
           tempLesson.lessonID = dlgLesson.LessonID();
           tempLesson.lastTime = dlgLesson.ClassHours();
           tempLesson.classroom = dlgLesson.Classroom();
           tempLesson.classGroup = dlgLesson.TeachingClass();
           tempLesson.gpa = dlgLesson.Credits();
           tempLesson.semester = dlgLesson.Semester();
           int teacherID = dlgLesson.TeacherID();

           m_TeacherManager.addLessonToTeacher(teacherID, tempLesson);

//           if(!m_LessonManager.lessons.isEmpty()){
//               qDebug()<<"ok";
//           }else{qDebug()<<"false";}

          ShowTeacherLessonInfoTable(teacherID);
       }
}

void MainWindow::on_actionDeleteLesson_triggered()
{

}

void MainWindow::on_actionAllTeachehr_triggered()
{
    //qDebug() << "Menu action triggered!";
    ShowTeacherInfoTable();
}


void MainWindow::on_actionDetailedTeacherInformation_triggered()
{

}

void MainWindow::on_actionLessonInformation_triggered()
{
    EnterTeacherIdDialog dlgTeacherId(this);
       int ret = dlgTeacherId.exec();
       if(ret==QDialog::Accepted)
       {
           Teacher tempteacher;
           tempteacher.ID=dlgTeacherId.Number();
           ShowTeacherLessonInfoTable(tempteacher.ID);
       }
}

void MainWindow::on_actionAdvancedSearch_triggered()
{
    SelectDialog dlgSelectDlg(this);
    int ret = dlgSelectDlg.exec();

    if(ret == QDialog::Accepted)
    {

        int typeID = dlgSelectDlg.m_iSelectIndex;
//        qDebug()<<"typeid in trigger"<<typeID;
        QString inputValue = dlgSelectDlg.GetValue();
        int radioType = dlgSelectDlg.m_iRadioID;
        QVariant valueData;


        if(typeID == 0 )
        {
            valueData = inputValue.toDouble();
        }
        else if (typeID == 1)
        {
            valueData = QDate::fromString(inputValue, "yyyy-MM-dd");
        }
        else
        {

            valueData = inputValue;
        }

        ShowSpecialList(typeID, radioType, valueData);
    }
}

void MainWindow::on_actionaddteacher_triggered()
{
    AddTeacherDialog dlgAdd(this);
        int ret = dlgAdd.exec();
        if(ret==QDialog::Accepted)
        {
            Teacher teacher;
            teacher.name = dlgAdd.Name();
            teacher.ID=dlgAdd.Id();
            teacher.sex=dlgAdd.Sex();
            teacher.birth=dlgAdd.BirthDate();
            teacher.degree=dlgAdd.Degree();
            teacher.rank=dlgAdd.Rank();
            teacher.salary=dlgAdd.Salary();
            teacher.isMarried=dlgAdd.IsMarried();
            m_TeacherManager.addTeacher(teacher);
            ShowTeacherInfoTable();
        }
}

void MainWindow::on_actionread_triggered()
{
    QString curPath = QDir::currentPath();
      QString dlgTitle = "选择一个文件";
      QString filter = "文本文件(*.txt);;所有文件(*.*)";
      QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
      if(aFileName.isEmpty())
          return;
      m_TeacherManager.loadFromFile(aFileName);
      ShowTeacherInfoTable();

}

void MainWindow::on_actionwrite_triggered()
{
    QString curPath = QDir::currentPath();
     QString dlgTitle = "另存为一个文件";
     QString filter = "文本文件(*.txt);;所有文件(*.*)";
     QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
     if(aFileName.isEmpty())
         return;
     m_TeacherManager.saveToFile(aFileName);

}
void MainWindow::on_ShowInfotableView_changed()
{
    QModelIndex index = ui->ShowInfotableView->currentIndex();
    int teacherRow = index.row();
    int Col = index.column();

    Teacher &teacher = m_TeacherManager.GetTeacher(teacherRow);
    QVariant data;

    switch (m_iCurTable)
    {
    case ShowType::TeacherInfo:
        data = teacherInfoModel->data(index);

        switch (Col)
        {
        case 0:
            teacher.ID = data.toInt();

            break;
        case 1:
            teacher.name = data.toString();
            break;
        case 2:
            teacher.sex = data.toString();
            break;
        case 3:
            teacher.birth = data.toDate();
            break;
        case 4:
            teacher.rank = data.toString();
            break;
        case 5:
            teacher.degree = data.toString();
            break;
        case 6:
            teacher.salary = data.toFloat();
            break;
        case 7:
            teacher.isMarried = data.toString();
            break;
        default:
            break;
        }
        ShowTeacherInfoTable();
        break;

    case ShowType::TeacherLessonInfo:
        data = lessonInfoModel->data(index);
        int lessonIndex = index.row();
            Lesson &lesson = teacher.lessons[lessonIndex];

            switch (Col)
            {
            case 0:
                lesson.lessonID = data.toInt();
                break;
            case 1:
                lesson.lessonName = data.toString();
                break;
            case 2:
                lesson.lastTime = data.toInt();
                break;
            case 3:
                lesson.classroom = data.toString();
                break;
            case 4:
                lesson.classGroup = data.toString();
                break;
            case 5:
                lesson.gpa = data.toFloat();
                break;
            case 6:
                lesson.semester = data.toString();
                break;
            default:
                break;

            ShowTeacherLessonInfoTable(teacher.ID);
        }
        break;
    }
}

void MainWindow::ShowSpecialList(int typeID, int RatioID, QVariant& valuedata)
{   //qDebug() << "Calling ShowSpecialList with parameters:" ;
    m_iCurTable = TeacherInfo;

        QStandardItemModel *teacherInfoModel = new QStandardItemModel();
        teacherInfoModel->setColumnCount(8);

        QStringList headerLabels;
        headerLabels << "编号"
                     << "姓名"
                     << "性别"
                     << "出生日期"
                     << "职称"
                     << "最高学历"
                     << "工资"
                     << "婚否";
        teacherInfoModel->setHorizontalHeaderLabels(headerLabels);

        int teacherNum = m_TeacherManager.GetTeacherNum();
        int rowIndex = 0;

    for (int i = 0; i < teacherNum; ++i)
    {
        //qDebug()<<typeID;

        Teacher tempTeacher = m_TeacherManager.GetTeacher(i);

        bool meetsCriteria = true;

        QVariant Var;

        switch (typeID)
                {
                case 0:
                    Var = tempTeacher.salary;
                    break;
                case 1:
                {
                    if (valuedata.canConvert<QDate>())
                    {
                        QDate filterDate = valuedata.toDate();
                        QDate birthDate = tempTeacher.birth;

                        meetsCriteria = (RatioID == 0 && birthDate < filterDate) ||
                                        (RatioID == 1 && birthDate == filterDate) ||
                                        (RatioID == 2 && birthDate > filterDate);

                        //qDebug()<<filterDate.year();
                       // qDebug()<<birthDate.year();

                    }
                    break;
                }
                case 2:
                    Var = tempTeacher.rank;
                    break;
                default:
                    meetsCriteria = false;
                    break;
                }

                if (meetsCriteria && typeID == 0 && valuedata.canConvert<double>())
                {
                    double salaryValue = valuedata.toDouble();
                    meetsCriteria = (RatioID == 0 && Var.toDouble() > salaryValue) ||
                                    (RatioID == 1 && Var.toDouble() == salaryValue) ||
                                    (RatioID == 2 && Var.toDouble() < salaryValue);
                }
                else if(meetsCriteria && typeID == 2 && valuedata.canConvert<QString>())
                {
                    QString rankValue = valuedata.toString();

                    meetsCriteria = (Var== rankValue);
                    qDebug()<<meetsCriteria;
                }
        //qDebug()<<meetsCriteria;
        //qDebug()<<meetsCriteria;
        //qDebug()<<teacherNum;

        if (meetsCriteria)
        {
            teacherInfoModel->setItem(rowIndex, 0, new QStandardItem(QString::number(tempTeacher.ID)));
            teacherInfoModel->setItem(rowIndex, 1, new QStandardItem(tempTeacher.name));
            teacherInfoModel->setItem(rowIndex, 2, new QStandardItem(tempTeacher.sex));
            teacherInfoModel->setItem(rowIndex, 3, new QStandardItem(tempTeacher.birth.toString("yyyy-MM-dd")));
            teacherInfoModel->setItem(rowIndex, 4, new QStandardItem(tempTeacher.rank));
            teacherInfoModel->setItem(rowIndex, 5, new QStandardItem(tempTeacher.degree));
            teacherInfoModel->setItem(rowIndex, 6, new QStandardItem(QString::number(tempTeacher.salary)));
            teacherInfoModel->setItem(rowIndex, 7, new QStandardItem(tempTeacher.isMarried));
            ++rowIndex;
        }
    }
    ui->ShowInfotableView->setModel(teacherInfoModel);

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    for (int i = 0; i < 8; ++i)
        ui->ShowInfotableView->setItemDelegateForColumn(i, readOnlyDelegate);
}
void MainWindow::onGetMousePos(QPoint pos)
{
    QModelIndex index = ui->ShowInfotableView->indexAt(pos);
    seletMouseRow = index.row();
    if(index.isValid())
        RightClickMenu->exec(QCursor::pos());

}

void MainWindow::onMenuAction(QAction *act)
{

//    if(m_iCurTable != TeacherInfo)
//        return;

    if(act->text() == "删除")
    {
        if(m_iCurTable==TeacherInfo){
        teacherInfoModel->removeRow(seletMouseRow);
        m_TeacherManager.RemoveTeacher(seletMouseRow);
        ui->ShowInfotableView->setModel(teacherInfoModel);
        }else if(m_iCurTable==TeacherLessonInfo){
            lessonInfoModel->removeRow(seletMouseRow);
            m_LessonManager.removeLesson(seletMouseRow);
            ui->ShowInfotableView->setModel(lessonInfoModel);
        }
    }
}


void MainWindow::on_actionclear_triggered()
{
    QString curPath = QDir::currentPath();
        QString dlgTitle = "选择一个文件清空";
        QString filter = "文本文件(*.txt);;所有文件(*.*)";
        QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
        if (aFileName.isEmpty())
            return;

        QFile file(aFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        file.close();
        m_TeacherManager.clearAllTeachers();
        ui->ShowInfotableView->setModel(teacherInfoModel);
        }

}

void MainWindow::on_actionclearwindow_triggered()
{
    m_TeacherManager.clearAllTeachers();
    qDebug()<<m_TeacherManager.teachers.size();
    ShowTeacherInfoTable();
}
