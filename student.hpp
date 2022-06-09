/**
 * file: student.hpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: Implementaion of student class which include all the student's details and courses.
*/

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "course.hpp"

class Student{
    public:
        Student():CLASS_LIMIT(5) {}
        
        void setStudentInfo(std::string studentName,int id,std::string major);
        void updateStudentName(std::string studentName);
        void updateStudentMajor(std::string major);
        void addCourse(const Course& courseObj);
        void dropCourse(Course& courseObj);
        void increseCourseLimit(int numberOfCoursesAllowed);
        void showAllCourses();
        void showStudyType();
        void updateStudyType();
        void calculateGPA();
        void printDetails() const;
        // getters
        int getStudentId() const;
        int getGpaInPercentage() const;
        int getSemesterCredits() const;
        double getGpa() const;
        std::string getFullName() const;
        
        bool searchTransferedCourse(std::string courseTitleAndNumber) const;
        void addTransferedCourse(std::string courseTitleAndNumber);
        
        bool searchPreviousCourse(std::string courseTitleAndNumber) const;
        void addPreviousCourse(const Course &course);
        std::vector<Course>&getCurrentCourses() {
            return currentCourses;
        }
        std::vector<Course>&getPreviousCourses() {
            return previousCourses;
        }
        std::vector<std::string>&getTransferedCourses() {
            return transferedCourses;
        }
        
        bool checkIfRequirementsAreMet(const Course &course);
    private:
        int studentId;
        // initially GPA start at 4.0
        double gpa = 4.0; 
        std::string studentFullname;
        std::string major;
        // copy of currently taking courses
        // Used for cheking before adding course
        std::vector<Course> currentCourses; 
        // copy of all previous courses
        // Used for cheking before adding course
        std::vector<Course> previousCourses; 
        // contains:(course Title and Numer), satisfied courses in other universities
        // Used for cheking before adding course
        std::vector<std::string> transferedCourses; 
        int CLASS_LIMIT;
        int totalSemesterCredits = 0;
        std::string type_of_study;
};

void Student::setStudentInfo(std::string studentName,int id,std::string major) {
    if (id < 0) {
        throw std::invalid_argument("Id canot be negative");
    }
    try {
        if (studentName == "") throw(20);
    } catch(int err) {
        if (err == 20) {
            std::cout << "\nNameExpectionOccured: please make sure to enter valid student name.\n";
            exit(20);
        }
    }
    studentFullname = studentName;
    studentId = id;
    major = major;
}

void Student::updateStudentName(std::string studentName) {
    try {
        if (studentName == "") throw(20);
    } catch(int err) {
        if (err == 20) {
            std::cout << "\nNameExpectionOccured: please make sure to enter valid student name.\n";
            exit(20);
        }
    }
    this->studentFullname = studentName;
}

void Student::updateStudentMajor( std::string major) {
    try {
        if (major == "") throw(21);
    } catch(int err) {
        if (err == 21) {
            std::cout << "\nNameExpectionOccured: please make sure to enter valid major name.\n";
            exit(21);
        }
    }
    this->major = major;
}

void Student::addCourse(const Course& courseObj) {
    if (currentCourses.size() == CLASS_LIMIT) {
        std::cout << "\nCourse limit reached! Department permission required to enroll.\n";
        return;
    }
    if (searchPreviousCourse(courseObj.getCourseAbbr())) {
        return;
    }
    if (searchTransferedCourse(courseObj.getCourseAbbr())) {
        return;
    }
    if (std::find(currentCourses.begin(), currentCourses.end(), courseObj) != currentCourses.end()) {
        std::cout << "Already enrolled in " << courseObj.getCourseAbbr() << std::endl;
        return;
    }
    totalSemesterCredits += courseObj.getCredit();
    currentCourses.push_back(courseObj);
    updateStudyType();
}

void Student::dropCourse( Course& courseObj) {
    if (currentCourses.empty()) {
        std::cout << "\nNothing to drop, student is not enrolled in any class.\n";
        return;
    }
    if (std::find(currentCourses.begin(), currentCourses.end(), courseObj) != currentCourses.end()) {
        std::cout << "\nCourse found: " << courseObj.getCourseAbbr() << "\n";
    }
    std::vector<Course>::iterator position = std::find(currentCourses.begin(), currentCourses.end(), courseObj);
    if (position != currentCourses.end()) {
        totalSemesterCredits -= courseObj.getCredit();
        currentCourses.erase(position);
        updateStudyType();
        courseObj.removeStudent(studentId);
        std::cout << courseObj.getCourseAbbr() << " was dropped\n";
        
    } else {
        std::cout << courseObj.getCourseAbbr() << " not found\n";
    }
}

void Student::increseCourseLimit(int numberOfCoursesAllowed) {
    if (numberOfCoursesAllowed <= 0) {
        std::cout << "\nCannot set limit to less than or equal to 0\n";
    }
    CLASS_LIMIT = numberOfCoursesAllowed;
}

void Student::showAllCourses() {
    std::cout << "All Courses: [";
    if (currentCourses.empty()) { std::cout << "Nothing to show!";}
    for (auto i : currentCourses) {
        std::cout << i.getCourseAbbr() << ',';
    }
    std::cout << "]\n";
}

void Student::showStudyType() {
    std::cout << "Study type this semester: " << type_of_study << "\n";
}

int Student::getStudentId() const {
    return studentId;
}

int Student::getSemesterCredits() const {
    return totalSemesterCredits;
}

void Student::updateStudyType() {
    if (totalSemesterCredits >= 12) {
        type_of_study = "full-time";
    } else {
        type_of_study = "part-time";
    }
}

// calcualte GPA using previous courses
void Student::calculateGPA() {
    int totalCreditHours = 0;
    double totalGradePoint = 0.0;
    for (auto course : previousCourses) {
        std::string letterGrade = course.getGrades(studentId);
        if (letterGrade == "A+" || letterGrade == "A") {
            totalGradePoint += 4;
        } else if (letterGrade == "A-") {
            totalGradePoint += 3.7;
        } else if (letterGrade == "B+") {
            totalGradePoint += 3.3;
        } else if (letterGrade == "B") {
            totalGradePoint += 3;
        } else if (letterGrade == "B-") {
            totalGradePoint += 2.7;
        } else if (letterGrade == "C+") {
            totalGradePoint += 2.3;
        } else if (letterGrade == "C") {
            totalGradePoint += 2;
        } else if (letterGrade == "C-") {
            totalGradePoint += 1.7;
        } else if (letterGrade == "D+") {
            totalGradePoint += 1.3;
        } else if (letterGrade == "D") {
            totalGradePoint += 1;
        } else if (letterGrade == "F") {
            totalGradePoint += 0;
        }
        totalCreditHours += course.getCredit();
    }
    
    gpa = (totalCreditHours * totalCreditHours)/totalCreditHours;
}

double Student::getGpa() const {
    return gpa;
}

int Student::getGpaInPercentage() const {
    return (gpa * 100)/4;
}

std::string Student::getFullName() const {
    return studentFullname;
}

void Student::printDetails() const {
    std::cout << 
        "------- Student Details -------\n"
        "Id: " << this->studentId << "\n"
        "Name: " << this->studentFullname << "\n"
        "Major: " << this->major << "\n"
        "GPA: " << this->gpa << "\n"
        "Total semester credits: " << this->totalSemesterCredits << "\n";
    std::cout << "Transfered courses: ";
    for (auto i : transferedCourses) {
        std::cout << i << " ";
    }
    std::cout << "\nPrevious courses: ";
    for (auto i : previousCourses) {
        std::cout << i.getCourseAbbr() << " ";
    }
    std::cout << "\nCurrent courses: ";
    for (auto i : currentCourses) {
        std::cout << i.getCourseAbbr() << " ";
    }
    std::cout << "\n------- End Student Details -------"<< std::endl;
}

bool Student::searchTransferedCourse(std::string courseTitleAndNumber) const {
    for (auto const &courseName : transferedCourses) {
        if (courseName == courseTitleAndNumber) return true;
    }
    return false;
}

void Student::addTransferedCourse(std::string courseTitleAndNumber) {
    if (!searchTransferedCourse(courseTitleAndNumber)) {
        transferedCourses.push_back(courseTitleAndNumber);
    }
}

bool Student::searchPreviousCourse(std::string courseTitleAndNumber) const {
    for (auto const &courseName : transferedCourses) {
        if (courseName == courseTitleAndNumber) return true;
    }
    return false;
}

// only currently enrolled classes can be added
void Student::addPreviousCourse(const Course &courseObj) {
    if (!searchPreviousCourse(courseObj.getCourseAbbr())) {
        if (currentCourses.empty()) {
            std::cout << "\nNothing to add, student is not enrolled in any class.\n";
            return;
        }
        if (std::find(currentCourses.begin(), currentCourses.end(), courseObj) != currentCourses.end()) {
            std::cout << "\nCourse found: " << courseObj.getCourseAbbr() << "\n";
        }
        std::vector<Course>::iterator position = std::find(currentCourses.begin(), currentCourses.end(), courseObj);
        if (position != currentCourses.end()) {
            currentCourses.erase(position);
            std::cout << courseObj.getCourseAbbr() << " added to previousCourses.\n";
            previousCourses.push_back(courseObj);
            
        } else {
            std::cout << courseObj.getCourseAbbr() << " not found\n";
        }
    }
}

bool Student::checkIfRequirementsAreMet(const Course &course) {
    for (auto &course : course.getArequisite()) {
        for (auto const &curent : currentCourses) {
            if (course == curent.getCourseAbbr()) {
                return false;
            }
        }
        for (auto const &prev : previousCourses) {
            if (course == prev.getCourseAbbr()) {
                return false;
            }
        }
        for (auto const &prev : transferedCourses) {
            if (course == prev) {
                return false;
            }
        }
    }
    for (auto const &course : course.getPrerequisite()) {
        bool check = false;
        for (auto const &prev : previousCourses) {
            if (course == prev.getCourseAbbr()) {
                check = true;
                break;
            }
        }
        if (!check) {
            for (auto const &prev : transferedCourses) {
                if (course == prev) {
                    check = true;
                    break;
                }
            }
        }
        if (!check) {
            return false;
        }
    }
    for (auto const &course : course.getCorequisite()) {
        bool check = false;
        for (auto const &prev : currentCourses) {
            if (course == prev.getCourseAbbr()) {
                check = true;
                break;
            }
        }
        for (auto const &prev : previousCourses) {
            if (course == prev.getCourseAbbr()) {
                check = true;
                break;
            }
        }
        for (auto const &prev : transferedCourses) {
            if (course == prev) {
                check = true;
                break;
            }
        }
        if (!check) {
            return false;
        }
    }
    return true;
}

#endif // End STUDENT_HPP
