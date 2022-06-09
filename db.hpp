/**
 * file: db.hpp
 * Author: Jinpa Tsering
 * Date: 6/4/2022
 * Description: Definition of Database class which holds semester list, 
 *              course list, student list, Instructor list.
*/

#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <vector>
#include <map>
#include "semester.hpp"
#include "course.hpp"
#include "student.hpp"
#include "instructor.hpp"

class DB{
    public:
        // getters
        std::vector<Semester>&getSemesterList(void) { return semestersList; }
        std::vector<Course>&getCourseList(void) { return coursesList; }
        std::vector<Student>&getStudentList(void) { return studentList; }
        std::vector<Instructor>&getInstructorList(void) { return instructorsList; }
        
        bool checkIfSemesterExists(std::string termAndYear) const;
        void addSemesterToDatabase(const Semester &newSemester);
        
        bool checkIfCourseExists(int courseId) const;
        void addCourseToDatabase(const Course &newCourse);
        
        bool checkIfStudentExists(int studentId) const;
        void addStudentToDatabase(const Student &newStudent);
        
        bool checkIfInstructorExists(int instructorId) const;
        void addInstructorToDatabase(const Instructor &newInstructor);
        
        void showSemesterDetail(std::string termAndYear);
        void showCourseDetail(int courseId);
        void showStudentDetail(int studentId);
        void showInstructorsDetail(int instructorId);
    private:
        std::vector<Semester> semestersList;
        std::vector<Course> coursesList;
        std::vector<Student> studentList;
        std::vector<Instructor> instructorsList;
};

bool DB::checkIfSemesterExists(std::string termAndYear) const {
    for (auto const &sems : semestersList) {
        if (sems.getTerm() == termAndYear) {
            return true;
        }
    }
    return false;
}

void DB::addSemesterToDatabase(const Semester &newSemester) {
    if (checkIfSemesterExists(newSemester.getTerm())) {
        return;
    }
    semestersList.push_back(newSemester);
}

bool DB::checkIfCourseExists(int courseId) const {
    for (auto const &course : coursesList) {
        if (course.getCourseId() == courseId) {
            return true;
        }
    }
    return false;
}

void DB::addCourseToDatabase(const Course &newCourse) {
    if (checkIfCourseExists(newCourse.getCourseId())) {
        return;
    }
    coursesList.push_back(newCourse);
}

bool DB::checkIfStudentExists(int studentId) const {
    for (auto const &student : studentList) {
        if (student.getStudentId() == studentId) {
            return true;
        }
    }
    return false;
}

void DB::addStudentToDatabase(const Student &newStudent) {
    if (checkIfStudentExists(newStudent.getStudentId())) {
        return;
    }
    studentList.push_back(newStudent);
}

bool DB::checkIfInstructorExists(int instructorId) const {
    for (auto const &instructor : instructorsList) {
        if (instructor.getInstructorId() == instructorId) {
            return true;
        }
    }
    return false;
}

void DB::addInstructorToDatabase(const Instructor &newInstructor) {
    if (checkIfInstructorExists(newInstructor.getInstructorId())) {
        return;
    }
    instructorsList.push_back(newInstructor);
}

void DB::showSemesterDetail(std::string termAndYear) {
    for (auto &sems : semestersList ) {
        if (sems.getTerm() == termAndYear) {
            sems.printDetails();
            return;
        }
    }
}

void DB::showCourseDetail(int courseId) {
    for (auto &course : coursesList) {
        if (course.getCourseId() == courseId) {
            course.printDetails();
            return;
        }
    }
}

void DB::showStudentDetail(int studentId) {
    for (auto &student : studentList ) {
        if (student.getStudentId() == studentId) {
            student.printDetails();
            return;
        }
    }
}

void DB::showInstructorsDetail(int instructorId) {
    for (auto &instructor: instructorsList ) {
        if (instructor.getInstructorId() == instructorId) {
            instructor.printDetails();
            return;
        }
    }
}

#endif // end DB_HPP