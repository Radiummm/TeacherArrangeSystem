#include "lesson.h"


Lesson& Lesson::operator=(const Lesson &other) {
    if (this == &other) {
        return *this;
    }

    lessonID = other.lessonID;
    lessonName = other.lessonName;
    lastTime = other.lastTime;
    classroom = other.classroom;
    classGroup = other.classGroup;
    gpa = other.gpa;
    semester = other.semester;

    return *this;
}
