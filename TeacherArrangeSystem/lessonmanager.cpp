#include "lessonmanager.h"
#include"lesson.h"
#include"teacher.h"
#include"teachermanager.h"
#include<qdebug.h>
void LessonManager::addLessonToTeacher(int teacherId,Lesson &lesson)
{
    TeacherManager temp;
    Teacher *teacher =temp.FIndTeacherById(teacherId);
    if (teacher)
    {
        teacher->lessons.append(lesson);
        this->lessons.append(lesson);
//        if(!lessons.isEmpty()){
//            qDebug()<<"true";
//        }else{qDebug()<<"no";}

    }

}

void  LessonManager::removeLesson(int id){
    for(int i=0;i<lessons.size();i++){
        if(lessons[i].lessonID==id){
            lessons.removeAt(i);
        }
    }
}
void LessonManager::clearAllLessons() {
    lessons.clear();
}
Lesson* LessonManager::FindLessonById(int id){
    for(int i=0;i<lessons.size();i++){
        if(lessons[i].lessonID==id){
            return &lessons[i];
        }
    }
    return nullptr;
}
QList<Lesson> LessonManager::getAllLesson(){
    return lessons;
}
