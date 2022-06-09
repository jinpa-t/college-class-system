/**
 * file: semseter.hpp
 * Author: Jinpa Tsering
 * Date: 5/31/2022
 * Description: Definition of Semester class which is responsible
 *              for handling Semester details and methods.
*/

#ifndef SEMESTER_HPP
#define SEMESTER_HPP

#include <iostream>
#include <vector>


// Seasons are declared int because it is easier to get user input as int.
enum Terms {Fall = 0, Winter = 1, Spring = 3, Summer = 4};

class Semester{
    public:
        Semester() { }
        void setTerm(int term,int year);
        void cancelCourse(int courseId);
        void addCourse(int courseId);
        std::string getTerm() const;
        const std::vector<int>*getCourses();
        void printDetails();
    private:
        Terms term; // fall, spring, summer, winter
        int termYear; // ex. 2021
        std::vector<int> offeredCourses;
};

void Semester::setTerm(int term, int year) {
    if (year < 2022) {
        throw std::invalid_argument("Invalid year: Year must be greater than or equal to 2022.");
    }
    if (term < 0 && term > 3) {
        throw std::invalid_argument("Invalid semester choice");
    }
    if (term == Terms::Fall) {
        this->term = Terms::Fall;
    } else if (term == Terms::Winter ) {
        this->term = Terms::Winter;
    }else if (term == Terms::Spring ) {
        this->term = Terms::Spring;
    }else if (term == Terms::Summer ) {
        this->term = Terms::Summer;
    }
    this->termYear = year;
}

std::string Semester::getTerm() const {
    if (term == Terms::Fall) {
        return "fall" + std::to_string(termYear);
    } else if (term == Terms::Winter) {
        return "winter" + std::to_string(termYear);
    
    } else if (term == Terms::Spring) {
        return "spring" + std::to_string(termYear);
    
    } else if (term == Terms::Summer) {
        return "summer" + std::to_string(termYear);
    }
    return "";
}

void Semester::addCourse(int courseId) {
    if (offeredCourses.size() == 0) {
        offeredCourses.push_back(courseId);
    } else if (std::find(offeredCourses.begin(), offeredCourses.end(), courseId) != offeredCourses.end())
        offeredCourses.push_back(courseId);
    else {
        std::cout << "Course is already added!" << std::endl;
    }
}

void Semester::cancelCourse(int courseId) {
    offeredCourses.erase(std::remove(offeredCourses.begin(), offeredCourses.end(), courseId), offeredCourses.end());
}

const std::vector<int>* Semester::getCourses() {
    return &offeredCourses;
}

void Semester::printDetails() {
    std::cout <<
        "------- Semester Details -------\n"
        "Semester: " << this->getTerm() << "\n"
        "Total offered classes: " << this->offeredCourses.size() << "\n"
        "------- End Semester Details -------"<< std::endl;
}

#endif // end SEMESTER_HPP
