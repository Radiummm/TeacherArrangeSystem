#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"teachermanager.h"
#include"lessonmanager.h"
#include <QMainWindow>
#include<QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum ShowType {
    TeacherInfo,
    SpecialList,
    TeacherLessonInfo
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ShowType m_iCurTable;
    QStandardItemModel * teacherInfoModel=nullptr;
    QStandardItemModel * lessonInfoModel=nullptr;
    TeacherManager m_TeacherManager;
    LessonManager m_LessonManager;
    void ShowTeacherInfoTable();
    void ShowLessonInfoTable(int id);
    void ShowTeacherDetailTable(int teacherId);
    void ShowTeacherLessonInfoTable(int teacherId);
    virtual void resizeEvent(QResizeEvent *event) override;
    void ShowSpecialList(int typeID, int RatioID, QVariant& valuedata);
    QMenu *RightClickMenu;                          //右键点击菜单
    QAction *deleteAction;                          //单行删除事件（如需要其它事件，可新定义）
    int     seletMouseRow;                          //选择到的表格的行数信息

private slots:
    void on_actionDeleteTeacher_triggered();

    void on_actionAddLesson_triggered();

    void on_actionDeleteLesson_triggered();

    void on_actionAllTeachehr_triggered();

    void on_actionDetailedTeacherInformation_triggered();

    void on_actionLessonInformation_triggered();

    void on_actionAdvancedSearch_triggered();

    void on_actionaddteacher_triggered();

    void on_actionread_triggered();

    void on_actionwrite_triggered();

     void on_ShowInfotableView_changed();

     void onGetMousePos(QPoint pos);               //菜单点击后获取当前位置
     void onMenuAction(QAction *act);              //事件操作


     void on_actioninput_triggered();

     void on_actionclear_triggered();

     void on_actionclearwindow_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
