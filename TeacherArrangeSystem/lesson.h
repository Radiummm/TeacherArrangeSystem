#ifndef LESSON_H
#define LESSON_H
#include<qstring.h>


class Lesson
{

public:
    int lessonID;
    QString lessonName;
    int lastTime;
    QString classroom;
    QString classGroup;
    int gpa;
    QString semester;
    Lesson& operator=(const Lesson& other);




};

#endif // LESSON_H
