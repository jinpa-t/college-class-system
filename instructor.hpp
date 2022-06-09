/**
 * file: instructor.hpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: Definition of Instructor class which is responsible
 *              for handling Instructor details and methods.
*/

#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>


class Instructor{
    public:
        Instructor():courseLimit(4) {}
        void setInstructorInfo(std::string instructorName,int id,std::string department);
        void addCourse(int courseId);
        void dropCourse(int courseId);
        void showAllCourses();
        void printInstructorType();
        int getInstructorId() const;
        int getNumOfSemesterCourses() const;
        std::vector<int>&getSemesterCourses();
        std::string getFullName() const;
        void updateInstructorType();
        void updateInstructorName(std::string name);
        void updateInstructorDepartment(std::string name);
        void updateInstructorCourseLimit(int limit);
        void printDetails() const;
    private:
        int instructorId;
        int totalSemesterCourses = 0;
        std::string instructorFullname;
        std::string department;
        int courseLimit = 0;
        std::string type_of_instructor;
        // To hold currently teaching courses
        std::vector<int> currentCourses; 
};

std::string Instructor::getFullName() const {
    return instructorFullname;
}

void Instructor::setInstructorInfo(std::string instructorName,int id,std::string department) {
    try {
        if (instructorName == "") throw(20);
    } catch(int err) {
        if (err == 20) {
            std::cout << "\nNameExpectionOccured: please make sure to enter valid Instructor name.\n";
            exit(20);
        }
    }
    instructorFullname = instructorName;
    instructorId = id;
    department = department;
}

void Instructor::addCourse(int courseId) {
    if (courseLimit == totalSemesterCourses) {
        std::cout << "\nCourse limit reached! Department permission required to enroll.\n";
    } else{
        totalSemesterCourses ++;
        //courseObj.setInstructor(instructorFullname);
        currentCourses.push_back(courseId);
        updateInstructorType();
    }
}

void Instructor::dropCourse(int courseId) {
    if (currentCourses.empty()) {
        std::cout << "\nNothing to drop, Instructor is not teaching any course.\n";
    } else {
        if (std::find(currentCourses.begin(), currentCourses.end(), courseId) != currentCourses.end()) {
            std::cout << "\nCourse found with Id = " << courseId << "\n";
        }
        std::vector<int>::iterator position = std::find(currentCourses.begin(), currentCourses.end(), courseId);
        if (position != currentCourses.end()) {
            totalSemesterCourses--;
            currentCourses.erase(position);
            updateInstructorType();
            std::cout << courseId << " is no longer taugh by "<< getFullName() << ".\n";
        } else {
            std::cout << courseId << " not found\n";
        }
    }
}

void Instructor::showAllCourses() {
    std::cout << "All Courses: [";
    if (currentCourses.empty()) { std::cout << "Nothing to show!\n";}
    for (auto i : currentCourses) {
        std::cout << i << ',';
    }
    std::cout << "]\n";
}

void Instructor::printInstructorType() {
    std::cout << "Instructor is: " << type_of_instructor << "\n";
}

int Instructor::getInstructorId() const {
    return instructorId;
}

int Instructor::getNumOfSemesterCourses() const {
    return totalSemesterCourses;
}

std::vector<int>& Instructor::getSemesterCourses() {
    return currentCourses;
}

void Instructor::updateInstructorType() {
    if (totalSemesterCourses >= 4) {
        type_of_instructor = "full professor";
    } else if (totalSemesterCourses == 2) {
        type_of_instructor = "associate professor";
    } else {
        type_of_instructor = "adjunt professor";
    }
}

void Instructor::updateInstructorName(std::string newName) {
    instructorFullname = newName;
}

void Instructor::updateInstructorDepartment(std::string department) {
    this->department = department;
}

void Instructor::updateInstructorCourseLimit(int limit) {
    courseLimit = limit;
}

void Instructor::printDetails() const {
    std::cout << 
        "------- Instructor Details -------\n"
        "Id: " << this->instructorId << "\n"
        "Name: " << this->instructorFullname << "\n"
        "Department: " << this->department << "\n"
        "type_of_instructor: " << this->type_of_instructor << "\n"
        "Totol semester courses: " << this->totalSemesterCourses << "\n"
        "------- End Instructor Details -------"<< std::endl;
}

#endif // End INSTRUCTOR_HPP
