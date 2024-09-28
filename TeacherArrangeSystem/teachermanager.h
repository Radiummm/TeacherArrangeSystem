#ifndef TEACHERMANAGER_H
#define TEACHERMANAGER_H
#include"teacher.h"

#include <QWidget>

class TeacherManager
{

public:


    void addTeacher(Teacher &m_teacher);
    void removeTeacher(int id);
    void addLessonToTeacher(int id,Lesson &lesson);
    void removeLessonFromTeacher(int teacherId,int lessonId);
    QList<Teacher> getAllTeachers();
    Teacher * FIndTeacherById(int id);
    QList<Teacher> FindTeacherByCondition(QString condition );
    QList<Teacher> teachers;
    void saveToFile(QString& filePath);
    void loadFromFile(QString& filePath);
    void clearAllTeachers() ;
    int GetTeacherNum();
    Teacher& GetTeacher(int index);
    int teacherNum;
    void RemoveTeacher(int index);
};

#endif // TEACHERMANAGER_H
