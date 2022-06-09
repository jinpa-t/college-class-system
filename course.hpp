/**
 * file: Course.hpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: Definition of Course class which is responsible
 *              for handling Course details and methods.
*/

#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <vector>
#include <map>


class Course{
    public:
        Course() { }
        bool operator==(const Course &rhs)const; // custom Course object == operator
        void setCourseInfo(int id, int credit, std::string abbr, std::string fullName,
                          std::string description, std::string designation );
        void setInstructor(const std::string instructorName);
        void addStudent(int newStudentId);
        void removeStudent(int newStudentId);
        void updateOpenStatus(int status);
        void showAllEnrolledStudents()const;
        void setGrades(int id, std::string grade);
        std::string getCourseAbbr() const;
        std::string getGrades(int id)const;
        bool findStudentById(int id)const;
        void printDetails();
        void setStudentLimit(int limit) {
            studentLimit = limit;
        }
        int getCredit()const {
            return courseCredit;
        }
        int getCourseId()const {
            return courseId;
        }
        
        void addArequisite(std::string name) {
            arequisite.push_back(name);
        }
        
        void addPrerequisite(std::string name) {
            prerequisite.push_back(name);
        }
        
        void addCorequisite(std::string name) {
            corequisite.push_back(name);
        }
        const std::vector<std::string>&getArequisite()const {
            return arequisite;
        }
        const std::vector<std::string>&getPrerequisite()const {
            return prerequisite;
        }
        const std::vector<std::string>&getCorequisite()const {
            return corequisite;
        }        
    private:
        int courseId;
        int courseCredit;
        int studentLimit;
        bool courseIsOpen = true; // courseIsOpen or closed
        std::string courseAbbr;
        std::string courseFullname;
        std::string courseDescription;
        std::string courseInstructor;
        std::string requirementDesignation;
        
        std::map<int,std::string> studentGrades;
        std::vector<int> currentStudentIds;
        // Coursees that must've taken before
        std::vector<std::string> prerequisite; 
        // Coursees that must be taken simultaneously
        std::vector<std::string> corequisite; 
        // cannot take if these Courses were taken
        std::vector<std::string> arequisite; 
};

bool Course::operator==(const Course &rhs) const {
    return rhs.courseId == courseId;
}

void Course::setCourseInfo(int id, int credit, std::string abbr, 
            std::string fullName,std::string description, std::string designation ) {
    courseId = id;
    courseCredit = credit;
    courseAbbr = abbr;
    courseFullname = fullName;
    courseDescription = description;
    requirementDesignation = designation;
}

std::string Course::getCourseAbbr() const { return courseAbbr;}

void Course::setInstructor(const std::string instructorName) {
    courseInstructor = instructorName;
}

void Course::addStudent(int newStudentId) {
    if (studentLimit == currentStudentIds.size() || !courseIsOpen) {
        std::cout << "Sorry, course is already full or closed!" << std::endl;
        return;
    }
    if (std::find(currentStudentIds.begin(),currentStudentIds.end(),newStudentId)!= currentStudentIds.end())
    {
        std::cout << "\nStudent already added to Course!\n";
    } else {
        currentStudentIds.push_back(newStudentId);
        std::cout << "\nStudent added to Course\n";
    }
    if (currentStudentIds.size() == studentLimit) {
        courseIsOpen = false;
    }
}

void Course::removeStudent(int _studentId) {
    if (0 == currentStudentIds.size()) {
        std::cout << "Nobody is enrolled in this course." << std::endl;
        return;
    }
    std::vector<int>::iterator studentIdPosition = std::find(currentStudentIds.begin(), currentStudentIds.end(), _studentId);
    if ( studentIdPosition!= currentStudentIds.end())
    {
        currentStudentIds.erase(studentIdPosition);
    } else {
        std::cout << "\nStudent not enrolled in the course\n";
    }
}

std::string Course::getGrades(int id) const {
    for (auto& [key,value] : studentGrades) {
        if (key == id) {
            return value;
        }
    }
    return "student not found";
}

void Course::setGrades(const int id, const std::string grade) {
    bool check = false;
    if ((grade[0] >= 'A' && grade[0] <= 'F')) {
        check = true;
    } else if (grade.length() == 2 && (grade[1] == '-' || grade[1] <= '+') &&
      (grade[0] >= 'A' && grade[0] <= 'F')) {
        check = true;
    }
    if (!check) {
        std::cout << "Invalid student grade!" << std::endl;
        return;
    }
    studentGrades[id] = grade;
    std::cout << "Success! Student grade set to: "<< grade << std::endl;
}

bool Course::findStudentById(int id)const {
    std::cout << currentStudentIds.size() << "\n";
    for (auto const &i : currentStudentIds) {
        if (i == id) return true;
    }
    return false;
}

void Course::showAllEnrolledStudents()const {
    std::cout << "All enrolled students: [";
    for (auto const &i : currentStudentIds) {
        std::cout << i << ", ";
    }
    std::cout << "]\n";
}

void Course::updateOpenStatus(int status) {
    courseIsOpen = status;
}

void Course::printDetails() {
    std::cout << 
        "------- Course Details -------\n"
        "Id: " << this->courseId << "\n"
        "Name: " << this->courseAbbr << "(" << this->courseFullname << ")\n"
        "Description: " << this->courseDescription << "\n"
        "Requirement Designation: " << this->requirementDesignation << "\n"
        "Instructor: " << this->courseInstructor << "\n"
        "Status: " << ((this->courseIsOpen)?"open":"closed") << "\n"
        "Credit Hour: " << this->courseCredit << "\n"
        "Totol Enrolled: " << this->currentStudentIds.size() << "/" << this->studentLimit << "\n";
    std::cout << "Prerequisite: ";
    for (auto i : prerequisite) {
        std::cout << i << " ";
    }
    std::cout << "\nCorequisite: ";
    for (auto i : corequisite) {
        std::cout << i << " ";
    }
    std::cout << "\nArequisite: ";
    for (auto i : arequisite) {
        std::cout << i << " ";
    }
    std::cout <<"\n------- Course Details -------"<< std::endl;
}

#endif // End COURSE_HPP
