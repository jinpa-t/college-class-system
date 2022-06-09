/**
 * file: helper.hpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: All the heplper functions are defined here.
*/

#ifndef HELPER_HPP
#define HELPER_HPP

#include<iostream>
#include <vector>
#include "db.hpp"
#include "semester.hpp"
#include "course.hpp"
#include "student.hpp"
#include "instructor.hpp"

int getCourseIdFromUser() {
    int courseId;
    std::cout << "Enter the course Id : ";
    std::cin >> courseId;
    return courseId;
}

int getInstructorIdFromUser() {
    int instructorId;
    std::cout << "Enter the instructor's Id : ";
    std::cin >> instructorId;
    return instructorId;
}

int getStudentIdFromUser() {
    int studentId;
    std::cout << "Enter the student's Id : ";
    std::cin >> studentId;
    return studentId;
}

std::string getSemesterFromUser() {
    int year, semester;
    std::string semesterYear;
    std::cout << "Enter the year: ";
    std::cin >> year;
    std::cout << "Enter the semester 0 = Fall, 1 = Winter, 2 = Spring, 3 = Summer: ";
    std::cin >> semester;
    
    if (semester == 0) {
        semesterYear = "fall";
    } else if (semester == 1) {
        semesterYear = "winter";
    } else if (semester == 2) {
        semesterYear = "spring";
    } else if (semester == 3) {
        semesterYear = "summer";
    }
    semesterYear += std::to_string(year);
    return semesterYear;
}

void createSemester(DB &db) {
    bool found = false;
    Semester newSem;
    int term, year;
    std::cout << "Enter the semester [0 = Fall,1 = Winter, 2 = Spring, 3 = Summer]: ";
    std::cin >> term;
    std::cout << "Enter the semester Year: ";
    std::cin >> year;
    newSem.setTerm(term, year);
    if (!db.checkIfSemesterExists(newSem.getTerm())) {
        db.addSemesterToDatabase(newSem);
        std::cout << "Semester successfully added!" << std::endl;
    } else {
        std::cout << "semester already exits" << std::endl;
    }
}

void createCourse(DB &db) {
    Course newCourse;
    int courseId, credit, courseSize;
    
    std::string abbr, fullCourseName, fullCourseDesc,courseDesignation;
    courseId = getCourseIdFromUser();
    
    if (db.checkIfCourseExists(courseId)) {
        std::cout << "Course with that id already exists." << std::endl;
        return;
    }
    std::cout << "Enter credit for the course : ";
    std::cin >> credit;
    std::cin.ignore();
    std::cout << "Enter abbreviation name for the course : ";
    std::getline(std::cin,abbr);
    std::cout << "Enter full name for the course : ";
    std::getline(std::cin,fullCourseName);
    std::cout << "Enter full description for the course : ";
    std::getline(std::cin,fullCourseDesc);
    std::cout << "Enter full designation for the course : ";
    std::getline(std::cin,courseDesignation);
    std::cout << "Enter the course size : ";
    std::cin >> courseSize;
    if (courseSize > 0) {
        newCourse.setStudentLimit(courseSize);
    }
    std::getline(std::cin,courseDesignation);
    newCourse.setCourseInfo(courseId,credit,abbr,fullCourseName,fullCourseDesc,courseDesignation);
    db.addCourseToDatabase(newCourse);
    std::cout << "Course successfully added!" << std::endl;
}

void createStudent(DB &db) {
    Student newStudent;
    int studentId = getStudentIdFromUser();
    std::string studentFullname,studentMajor;
    if (!db.checkIfStudentExists(studentId)) {
        std::cin.ignore(); // prevent getline skipping
        std::cout << "Enter student's fullname : ";
        getline(std::cin,studentFullname);
        
        std::cout << "Enter student's major : ";
        getline(std::cin,studentMajor);
        newStudent.setStudentInfo(studentFullname,studentId,studentMajor);
        db.addStudentToDatabase(newStudent);
        std::cout << "Student successfully added!" << std::endl;
    }
}

void createInstructor(DB &db) {
    Instructor newInstructor;
    std::string instructorFullname,instructorDepartment;
    int instructorId = getInstructorIdFromUser();
    if (!db.checkIfInstructorExists(instructorId)) {
        std::cin.ignore();
        std::cout << "Enter instructor's fullname : ";
        getline(std::cin,instructorFullname);
        
        std::cout << "Enter instructor's department : ";
        getline(std::cin,instructorDepartment);
        newInstructor.setInstructorInfo(instructorFullname,instructorId,instructorDepartment);
        std::cout << "Instructor successfully added!" << std::endl;
        db.addInstructorToDatabase(newInstructor);
    }
}

void searchSemester(const DB &db) {
    std::string semesterYear = getSemesterFromUser();
    if (db.checkIfSemesterExists(semesterYear)) {
        std::cout << "Semester found!" << std::endl;
    } else {
        std::cout << "Semester found!" << std::endl;
    }
}

void searchCourse(const DB &db) {
    int courseId = getCourseIdFromUser();
    if (db.checkIfCourseExists(courseId)) {
        std::cout << "Course with id = " << courseId << " found!" << std::endl;
    } else{
        std::cout << "Course with id = " << courseId << " not found!" << std::endl;
    }
}

void searchStudent(const DB &db) {
    int studentId = getStudentIdFromUser();
    if (db.checkIfStudentExists(studentId)) {
        std::cout << "Student with id = " << studentId << " found!" << std::endl;
    } else{
        std::cout << "Student with id = " << studentId << " not found!" << std::endl;
    }
}

void searchInstructor(const DB &db) {
    int instructorId = getInstructorIdFromUser();
    if (db.checkIfInstructorExists(instructorId)) {
        std::cout << "Instructor with id = " << instructorId << " found!" << std::endl;
    } else{
        std::cout << "Instructor with id = " << instructorId << " not found!" << std::endl;
    }
}

void addCourseToSemester(DB &bd) {
    if (bd.getSemesterList().empty()) {
        std::cout << "You must first create a Semester" << std::endl;
        exit(1);
    }
    int courseId;
    std::string semesterYear = getSemesterFromUser();
    bool findSem = false;
    bool courseFound = false;
    for (auto &i : bd.getSemesterList()) {
        if (i.getTerm() == semesterYear) {
            findSem = true;
            std::cout << "Semester Found!" << std::endl;
            courseId = getCourseIdFromUser();
            for (auto &j : bd.getCourseList()) {
                if ( j.getCourseId() == courseId) {
                    courseFound = true;
                    i.addCourse(j.getCourseId());
                    std::cout << "Course added!" << std::endl;
                    break;
                }
            }
            break;
        }
    }
    if (!findSem) {
        std::cout << "Semester not found!" << std::endl;
    }
    if (!courseFound) {
        std::cout << "Course with id = " << courseId << " not found!" << std::endl;
    }
}

void addStudentToCourse(DB &db) {
    if (db.getCourseList().empty()) {
        std::cout << "You must first create a Course" << std::endl;
        exit(1);
    }
    int studentId, courseId = getCourseIdFromUser();
    bool courseFound = false, studentFound = false;
    for (auto &course : db.getCourseList()) {
        if (course.getCourseId() == courseId) {
            courseFound = true;
            studentId = getStudentIdFromUser();
            std::cout << "Course found!" << std::endl;
            for (auto &student : db.getStudentList()) {
                if (student.getStudentId() == studentId) {
                    studentFound = true;
                    if (student.checkIfRequirementsAreMet(course)) {
                        // add student to course
                        course.addStudent(student.getStudentId());
                        // add course to student
                        student.addCourse(course);
                        std::cout << "Student added to course" << std::endl;
                    } else {
                        std::cout << "Student did not meet the course requirments!" << std::endl;
                    }
                    break;
                }
            }
            break;
        }
    }
    if (!courseFound) {
        std::cout << "Course not found!" << std::endl;
    }
    if (!studentFound) {
        std::cout << "Student with id = " << studentId << " not found!" << std::endl;
    }
    
}

void addInstructorToCourse(DB &db) {
    if (db.getCourseList().empty()) {
        std::cout << "You must first create a Course" << std::endl;
        exit(1);
    }
    int instructorId, courseId = getCourseIdFromUser();
    bool courseFound = false, instructorFound = false;
    for (auto &course : db.getCourseList()) {
        if (course.getCourseId() == courseId) {
            courseFound = true;
            instructorId = getInstructorIdFromUser();
            for (auto &instructor : db.getInstructorList()) {
                if (instructor.getInstructorId() == instructorId) {
                    course.setInstructor(instructor.getFullName());
                    instructor.addCourse(course.getCourseId());
                    instructorFound = true;
                    break;
                }
            }
            break;
        }
    }
    if (!courseFound) {
        std::cout << "Course not found!" << std::endl;
    }
    if (!instructorFound) {
        std::cout << "Instructor with id = " << instructorId << " not found!" << std::endl;
    }
}

void updateSemester(DB &db) {
    if (db.getSemesterList().empty()) {
        std::cout << "You must first create a Semester" << std::endl;
        exit(1);
    }
    int courseId;
    std::string semesterYear = getSemesterFromUser();
    bool findSem = false;
    for (auto &sem : db.getSemesterList()) {
        if (sem.getTerm() == semesterYear) {
            findSem = true;
            int updateChoice;
            std::cout << "Select one of the following to update\n"
                         "[1 = Term and Year, 2 = remove course]: ";
            std::cin >> updateChoice;
            if (updateChoice == 1) {
                int newTerm,newYear; 
                std::cout << "Current term: " << sem.getTerm() << std::endl;
                std::cout << "Enter new term[0 = fall, 1 = winter, 2 = spring, 3 = summer]: ";
                std::cin >> newTerm;
                std::cout << "Enter new year for the semester: ";
                std::cin >> newYear;
                sem.setTerm(newTerm,newYear);
            } else if (updateChoice == 2) {
                int courseId;
                std::cout << "Enter the id of the course to remove: ";
                std::cin>> courseId;
                sem.cancelCourse(courseId);
            }
            
            break;
        }
    }
    if (!findSem) {
        std::cout << "Semester not found!" << std::endl;
    }
}

void updateCourse(DB &db) {
    int courseId = getCourseIdFromUser();
    bool courseFound = false;
    for (auto &course : db.getCourseList()) {
        if ( course.getCourseId() == courseId) {
            courseFound = true;
            int studentLimit, updateCourseChoice, openStatus;
            std::string courseInstructor;
            std::cout << "Select one of the following to update\n"
                         "[1 = studentLimit, 2 = openStatus, 3 = courseInstructor]: ";
            std::cin >> updateCourseChoice;
            if (updateCourseChoice == 1) {
                std::cout << "Enter the new course student limit: ";
                std::cin >> studentLimit;
                course.setStudentLimit(studentLimit);
            } else if (updateCourseChoice == 2) {
                std::cout << "Enter the new course status[0 = close, 1 = open : ";
                std::cin >> openStatus;
                if (openStatus == 1) {
                    course.updateOpenStatus(openStatus);
                } else if (openStatus == 0) {
                    course.updateOpenStatus(openStatus);
                }
            } else if (updateCourseChoice == 3) {
                std::cout << "Enter the new course instructor: ";
                std::cin.ignore();
                getline(std::cin, courseInstructor);
                course.setInstructor(courseInstructor);
            }
            
            break;
        }
    }
    if (!courseFound) {
        std::cout << "Course with id = " << courseId << " not found!" << std::endl;
    }
}

void updateStudent(DB &db) {
    std::string studentFullname,studentMajor;
    int studentId = getStudentIdFromUser();
    
    bool studentFound = false;
    for (auto &student : db.getStudentList()) {
        if (student.getStudentId() == studentId) {
            studentFound = true;
            int studUpdChoice;
            std::cout << "Select one of the following to update\n"
                         "[1 = update name, 2 = update major]: ";
            std::cin >> studUpdChoice;
            std::cin.ignore(); // prevent getline skipping
            if (studUpdChoice == 1) {
                std::cout << "Enter student's new fullname : ";
                getline(std::cin,studentFullname);
                student.updateStudentName( studentFullname);
            } else if (studUpdChoice == 2) {
                std::cout << "Enter student's major : ";
                getline(std::cin,studentMajor);
                student.updateStudentMajor(studentMajor);
            }
            break;
        }
    }
    if (!studentFound) {
        std::cout << "Student not found!" << std::endl;
    }
}

void updateInstructor(DB &db) {
    // update instructor informations
    int instructorId = getInstructorIdFromUser();
    bool instructorFind = false;
    for (auto &instructor : db.getInstructorList()) {
        if ( instructor.getInstructorId() == instructorId) {
            instructorFind = true;
            std::string instructorFullname,department;
            int courseLimit, instrucUpdchoice;
            std::cout << "Select one of the following to update\n"
                         "[1 = name, 2 =  department, 3 = course limit]: ";
            std::cin >> instrucUpdchoice;
            std::cin.ignore();
            if (instrucUpdchoice == 1) {
                std::cout << "Enter instructor's new fullname: ";
                getline(std::cin, instructorFullname);
                instructor.updateInstructorName(instructorFullname);
            } else if (instrucUpdchoice == 2) {
                std::cout << "Enter instructor's new department: ";
                getline(std::cin, department);
                instructor.updateInstructorDepartment(department);
            } else if (instrucUpdchoice == 3) {
                std::cout << "Enter instructor's new course Limit: ";
                std::cin >> courseLimit;
                instructor.updateInstructorCourseLimit(courseLimit);
            }
            
            break;
        }
    }
    if (!instructorFind) {
        std::cout << "Instructor with id = " << instructorId << " not found!" << std::endl;
    }
}

void updateStudentGrade(DB &db) {
    // get id of prof.-> get Id of course -> getStudentId = enter grade;
    int instructorId;
    std::string grade;
    instructorId = getInstructorIdFromUser();
    bool instructorFind = false;
    int index = 0;
    for (auto const &instructor : db.getInstructorList()) {
        if ( instructor.getInstructorId() == instructorId) {
            instructorFind = true;
            break;
        }
        index++;
    }
    if (!instructorFind) {
        std::cout << "The instructor Id does not exist." << std::endl;
        exit(0);
    }
    bool instructorIsTeachingThisCourse = false, studentIsEntrolled = false, courseFound = false;
    int courseId = getCourseIdFromUser();
    int index2 = 0;
    for (auto const &course : db.getCourseList()) {
        if ( course.getCourseId() == courseId) {
            instructorFind = true;
            break;
        }
        index2++;
    }
    for (auto const &teachingCourseId : db.getInstructorList()[index].getSemesterCourses()) {
        if (teachingCourseId == courseId) {
            instructorIsTeachingThisCourse = true;
            int studentId = getStudentIdFromUser();
            std::cin.ignore();
            for (auto &student : db.getStudentList()) {
                if ((student.getStudentId() == studentId && db.getCourseList()[index2].findStudentById(studentId))) {
                    studentIsEntrolled = true;
                    std::cout << "Enter the letter grade[A-F]: ";
                    std::cin >> grade;
                    db.getCourseList()[index2].setGrades(studentId,grade);
                    student.addPreviousCourse(db.getCourseList()[index2]);
                    break;
                }
            }
            break;
        }
    }
    if (!instructorIsTeachingThisCourse) {
        std::cout << "The instructor is not teaching this course." << std::endl;
    }
    if (!studentIsEntrolled) {
        std::cout << "The student is not enrolled in this course." << std::endl;
    }
}

void showAllSemesters( DB &db) {
    std::cout << "All semesters: [";
    for (auto const &sem : db.getSemesterList()) {
        std::cout << sem.getTerm() << " ";
    }
    std::cout << "]" << std::endl;
}

void showAllCourses( DB &db) {
    std::cout << "All courses: [";
    for (auto const &course : db.getCourseList()) {
        std::cout << course.getCourseAbbr() << " ";
    }
    std::cout << "]" << std::endl;
}

void showAllStudents( DB &db) {
    std::cout << "All students: [";
    for (auto const &student : db.getStudentList()) {
        std::cout << student.getFullName() << " ";
    }
    std::cout << "]" << std::endl;
}

void showAllInstructors( DB &db) {
    std::cout << "All instructors: [";
    for (auto const &inst : db.getInstructorList()) {
        std::cout << inst.getFullName() << " ";
    }
    std::cout << "]" << std::endl;
}

void addRequisitesToCourse( DB &db) {
    int courseId = getCourseIdFromUser();
    for (auto &course : db.getCourseList()) {
        if ( course.getCourseId() == courseId) {
            std::string userInput;
            std::cout << "Enter 'n' to exit.";
            do {
                std::cout << "Enter pre-requisite course Abbr: ";
                getline(std::cin, userInput);
                if (userInput.length()!= 0 && userInput != "n") {
                    course.addPrerequisite(userInput);
                }
            } while(userInput != "n");
            userInput = "";
            std::cout << "Enter 'n' to exit.";
            do {
                std::cout << "Enter co-requisite course Abbr: ";
                getline(std::cin, userInput);
                if (userInput.length()!= 0 && userInput != "n") {
                    course.addCorequisite(userInput);
                }
            } while(userInput != "n");
            userInput = "";
            std::cout << "Enter 'n' to exit.";
            do {
                std::cout << "Enter Arequisite course Abbr: ";
                getline(std::cin, userInput);
                if (userInput.length()!= 0 && userInput != "n") {
                    course.addArequisite(userInput);
                }
            } while(userInput != "n");
        }
    }
}

void addTransferedCoursesToStudent(DB &db) {
    int studentId = getStudentIdFromUser();
    bool studentFound = false;
    for (auto &student : db.getStudentList()) {
        if (student.getStudentId() == studentId) {
            std::string userInput;
            std::cout << "Enter 'n' to exit.";
            do {
                std::cout << "Enter transfered course: ";
                getline(std::cin, userInput);
                if (userInput.length()!= 0 && userInput != "n") {
                    student.getTransferedCourses().push_back(userInput);
                }
            } while(userInput != "n");
        }
    }
}

#endif //end HELPER_HPP
