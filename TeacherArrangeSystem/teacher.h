    #ifndef TEACHER_H
#define TEACHER_H
#include<QDate>

#include"lesson.h"
class Teacher
{

public:
    int ID;
    QString name;
    QString sex;
    QDate birth;
    QString rank;
    QString degree;
    double salary;
    QString isMarried;
    QList<Lesson> lessons;

    Teacher& operator=(const Teacher &other);


};

#endif // TEACHER_H
