#include "teachermanager.h"
#include"teacher.h"
#include<QFile>
#include"lesson.h"
#include<QTextStream>
#include<QDebug>
void TeacherManager::addTeacher(Teacher &m_teacher){
    teachers.append(m_teacher);
}
void TeacherManager::removeTeacher(int id){
    for(int i=0;i<teachers.size();i++){
        if(teachers[i].ID==id)
        {
            teachers.removeAt(i);
        }
    }
}
void TeacherManager::clearAllTeachers() {
    teachers.clear();
}
void TeacherManager::addLessonToTeacher(int id,Lesson &lesson)
{
    Teacher * tempTeacher=FIndTeacherById(id);
    if(tempTeacher){
        tempTeacher->lessons.append(lesson);
    }
}
int TeacherManager::GetTeacherNum()  {
    return teachers.size();
}
void TeacherManager::RemoveTeacher(int index)
{
    if (index >= 0 && index < teachers.size())
    {
        teachers.erase(teachers.begin() + index);
        teacherNum--;
    }
}

void TeacherManager::removeLessonFromTeacher(int teacherId,int lessonId){
    for(int i=0;i<teachers.size();i++){
        for(int j=0;j<teachers[i].lessons.size();j++){
            if(teachers[i].lessons[j].lessonID==lessonId&&teachers[i].ID==teacherId){
                teachers[i].lessons.removeAt(j);
            }
        }
    }
}
QList<Teacher> TeacherManager::getAllTeachers(){
    return teachers;
}
Teacher * TeacherManager::FIndTeacherById(int id){
//    qDebug()<<teachers.size()<<"999999";
    for(int i=0;i<teachers.size();i++){
        if(teachers[i].ID==id)
        {
          return &teachers[i];
        }

    }

    return nullptr;
}
QList<Teacher> TeacherManager::FindTeacherByCondition(QString condition ){
    QList<Teacher> result;
    for(auto &tempteacher:teachers){
        if(condition=="unmarried"){
            result.append(tempteacher);
        }
        else {
                result.append(tempteacher);
        }
    }
    return result;

}
void TeacherManager::saveToFile(QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Teacher& teacher : teachers) {
            out << teacher.ID << " " << teacher.name << " " << teacher.sex << " "
                << teacher.birth.year() << " " << teacher.birth.month() << " " << teacher.birth.day() << " "
                << teacher.rank << " " << teacher.degree << " " << teacher.salary << " " << teacher.isMarried
                << " |";

            if (teacher.lessons.isEmpty()) {
                out << "END";
            } else {
                for (const Lesson& lesson : teacher.lessons) {
                    out << " " << lesson.lessonID << " " << lesson.lessonName << " "
                        << lesson.lastTime << " " << lesson.classroom << " "
                        << lesson.classGroup << " " << lesson.gpa << " "
                        << lesson.semester;
                }
            }
            out << "\n";
        }
        file.close();
    } else {
        qDebug() << "Failed to open file for writing:" << file.errorString();
    }
}

void TeacherManager::loadFromFile( QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) {
                continue;
            }
            QStringList parts = line.split('|');

            Teacher teacher;
            int year, month, day;

            QStringList teacherInfo = parts[0].split(' ');
            if (teacherInfo.size() >= 10) {
                teacher.ID = teacherInfo[0].toInt();
                teacher.name = teacherInfo[1];
                teacher.sex = teacherInfo[2];
                year = teacherInfo[3].toInt();
                month = teacherInfo[4].toInt();
                day = teacherInfo[5].toInt();
                teacher.rank = teacherInfo[6];
                teacher.degree = teacherInfo[7];
                teacher.salary = teacherInfo[8].toDouble();
                teacher.isMarried = teacherInfo[9];
                teacher.birth.setDate(year, month, day);
            } else {
                qDebug() << "Teacher info format error, not enough fields:" << teacherInfo;
                continue;
            }

            QStringList lessonInfo = parts[1].split(' ',QString::SkipEmptyParts);
            if (lessonInfo.isEmpty()) {        
                teachers.append(teacher);
                continue;
            }

            if (lessonInfo[0] == "END") {
                teachers.append(teacher);
                continue;
            }

            for (int i = 0; i < lessonInfo.size(); i += 7) {
                if (i + 6 >= lessonInfo.size()) break;

                Lesson lesson;
                lesson.lessonID = lessonInfo[i].toInt();
                lesson.lessonName = lessonInfo[i+1];
                lesson.lastTime = lessonInfo[i+2].toInt();
                lesson.classroom = lessonInfo[i+3];
                lesson.classGroup = lessonInfo[i+4];
                lesson.gpa = lessonInfo[i+5].toDouble();
                lesson.semester = lessonInfo[i+6];

                teacher.lessons.append(lesson);
            }

            teachers.append(teacher);
        }
        file.close();
    } else {
        qDebug() << "Failed to open file for reading:" << file.errorString();
    }
}


Teacher& TeacherManager::GetTeacher(int index)
{
    if (index >= 0 && index < teachers.size())
    {
        return teachers[index];
    }
    else
    {
        throw std::out_of_range("Invalid index for Teacher array");
    }
}

