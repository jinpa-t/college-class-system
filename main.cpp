/**
 * file: main.cpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: Create, manage semester, course, studnet, and professor.
*/

#include <iostream>
#include "db.hpp"
#include "semester.hpp"
#include "course.hpp"
#include "student.hpp"
#include "instructor.hpp"
#include "helper.hpp"


int main()
{
    DB db;
    
    Semester winter2022; 
    winter2022.setTerm(Terms::Winter,2022);
    
    
    Course eng101 =  Course(); 
    eng101.setCourseInfo(1,3,"ENG101","English 101","Intro to English 101", "General Education"); 
    winter2022.addCourse(eng101.getCourseId());
    std::cout << "\nCurrently offered courses: ";
    for(auto i: *winter2022.getCourses())
        std::cout << i << ",";
    std::cout << std::endl;
    eng101.setStudentLimit(10);
    Instructor newInstructor;
    newInstructor.setInstructorInfo("Jane Doe",1,"");
    
    eng101.setInstructor(newInstructor.getFullName()); 
    newInstructor.addCourse(eng101.getCourseId());
    
    newInstructor.printInstructorType();
    std::cout << "Instructor " << newInstructor.getFullName() << " is teaching " 
              << newInstructor.getNumOfSemesterCourses() << " courses.\n";
    
    Student newStudent; 
    newStudent.setStudentInfo("John Doe",1010,""); // setStudentInfo(name, id,major)
    std::cout << "GPA: "<<  newStudent.getGpa() << " or " << newStudent.getGpaInPercentage() << "%\n";
    
    eng101.addStudent(newStudent.getStudentId());
    newStudent.addCourse(eng101); // takes by reference
    
    std::cout << "Student's total semester Credits: " << newStudent.getSemesterCredits() << std::endl;
    newStudent.showAllCourses();
    eng101.showAllEnrolledStudents();
    newStudent.dropCourse(eng101); // takes by reference
    std::cout << "Student's total semester Credits: " << newStudent.getSemesterCredits() << std::endl;
    newStudent.showAllCourses();
    newStudent.showStudyType();
    
    db.addCourseToDatabase(eng101);
    db.addInstructorToDatabase(newInstructor);
    db.addStudentToDatabase(newStudent);
    db.addSemesterToDatabase(winter2022);
    
    int choice;
    do {
        std::cout << 
            "\nPlease select one of the following options:\n"
             "1 To Create\n"
             "2 To Search\n"
             "3 To add\n"
             "4 To Update\n"
             "5 To Show\n"
             "6 To exit\n";
        std::cin >> choice;
        if(choice == 1) {
            // create semester and add it to the semesters vector
            int choice2;
            std::cout << "Select one of the following to create\n"
                         "1 = Semester, 2 = Course, 3 = Student, 4 = Instructor: ";
            std::cin >> choice2;
            if(choice2 == 1) {
                createSemester(db); // takes by reference
            } else if(choice2 == 2) {
                // create a course and add it to the right semester.
                createCourse(db); 
            } else if(choice2 == 3) {
                // create a student and add it to the students list.
                createStudent(db);
            } else if(choice2 == 4) {
                // create Instructor and add it to the instructors list;
                createInstructor(db);
            }
        } else if(choice == 2) {
            int searchChoice;
            std::cout << "Select one from the following option to search\n"
                         "1 = semester, 2 = course, 3 = student, 4 = professor\n";
            std::cin >> searchChoice;
            if(searchChoice == 1) {
                searchSemester(db);
            } else if(searchChoice == 2) {
                searchCourse(db);
            } else if(searchChoice == 3) {
                searchStudent(db);
            } else if(searchChoice == 4) {
                searchInstructor(db);
            }
        } else if(choice == 3) {
            //add setInstructor for course, register student to course.
            std::cout <<
                "Enter 1 to add course to semester\n"
                "Enter 2 to add student to a course\n"
                "Enter 3 to add instructor to a course\n"
                "Enter 4 to add transfered course to student\n"
                "Enter 5 to add co, pre, and arequisite to course\n";
            int addChoice;
            std::cin >> addChoice;
            if(addChoice == 1) {
                addCourseToSemester(db);
            } else if(addChoice == 2) {
                addStudentToCourse(db);
            } else if(addChoice == 3) {
                addInstructorToCourse(db);
            } else if(addChoice == 4) {
                addTransferedCoursesToStudent(db);
            } else if(addChoice == 5) {
                addRequisitesToCourse(db);
            }
        } else if(choice == 4) {
            // update details about course or student or instructor or semester 
            std::cout << "Select one of the following to update:\n"
            "1 = semester, 2 = course, 3 = student, 4 = professor, 5 = grade\n";
            int updChoice;
            std::cin >> updChoice;
            if(updChoice == 1) {
                updateSemester(db);
            } else if(updChoice == 2) {
                updateCourse(db);
            }  else if(updChoice == 3) {
                updateStudent(db);
            }  else if(updChoice == 4) {
                updateInstructor(db);
            } else if(updChoice == 5) {
                updateStudentGrade(db);
            }
        } else if(choice == 5) {
            std::cout << 
                "Select one of the following to show\n"
                "[1 = Semesters, 2 = Courses, 3 = Students, 4 = Instructors,\n"
                "5 = Semester detail, 6 = Course detail, 7 = Student detail," 
                "8 = Instructor detail]: ";
            int choice3;
            std::cin >> choice3;
            if(choice3 == 1) {
                showAllSemesters(db);
            } else if(choice3 == 2) {
                showAllCourses(db);
            } else if(choice3 == 3) {
                showAllStudents(db);
            } else if(choice3 == 4) {
                showAllInstructors(db);
            }else if(choice3 == 5) {
                db.showSemesterDetail(getSemesterFromUser());
            }else if(choice3 == 6) {
                db.showCourseDetail(getCourseIdFromUser());
            }else if(choice3 == 7) {
                db.showStudentDetail(getStudentIdFromUser());
            }else if(choice3 == 8) {
                db.showInstructorsDetail(getInstructorIdFromUser());
            }
        }
    } while(choice != 6);
    
    return 0;
}
