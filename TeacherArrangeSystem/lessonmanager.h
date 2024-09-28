#ifndef LESSONMANAGER_H
#define LESSONMANAGER_H
#include"teacher.h"
#include"lesson.h"


class LessonManager
{

public:

    void addLesson(Lesson &lesson);
    void removeLesson(int id);
    Lesson* FindLessonById(int id);
    QList<Lesson> getAllLesson();
    QList<Lesson> lessons;    
    void clearAllLessons() ;
    void addLessonToTeacher(int teacherId, Lesson &lesson);
};

#endif // LESSONMANAGER_H
