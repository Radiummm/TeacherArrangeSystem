#include "teacher.h"


Teacher& Teacher::operator=(const Teacher &other) {
    if (this == &other) {
        return *this;
    }

    ID = other.ID;
    name = other.name;
    sex = other.sex;
    birth = other.birth;
    rank = other.rank;
    degree = other.degree;
    salary = other.salary;
    isMarried = other.isMarried;
    lessons = other.lessons;

    return *this;
}
