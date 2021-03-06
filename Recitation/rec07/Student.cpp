#include "Course.hpp"
#include "Student.hpp"
using namespace std;

namespace BrooklynPoly {
    // Student Implemetation Codes
    ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name << ":";
        if (rhs.courses.empty()) {
            os << " No Courses";
        } else {
            for (Course* coursep : rhs.courses) {
                os << " " << coursep->getName();
            }
        }
        os << endl;
        return os;
    }

    // Student methods needed by Registrar
    Student::Student(const string& theName) : name(theName) {}
    const string& Student::getName() const { return name; }
    void Student::setName(const string& newName) { name = newName; }

    bool Student::addCourse(Course* add_coursep) {
        for (Course* coursep : courses) {
            if (coursep->getName() == add_coursep->getName()) {
                return false;
            }
        }
        courses.push_back(add_coursep);
        return true;
    }

    // Student method needed by Course
    void Student::removedFromCourse(Course* removed_coursep) {
        size_t i;
        for (i = 0; i < courses.size(); i++) {
            if (courses[i] == removed_coursep) {
                break;
            }
        }
        courses[i] = courses.back();
        courses.pop_back();
    }

    void Student::dropFromCourses() {
        for (Course* coursep : courses) {
            coursep->dropStudent(this);
        }
        courses.clear();
    }

}  // namespace BrooklynPoly
