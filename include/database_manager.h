#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "student.h"
#include "subject.h"
#include "grade.h"

class DatabaseManager {
private:
    sql::Driver* driver;
    sql::Connection* con;

public:
    DatabaseManager();
    ~DatabaseManager();

    // Student operations
    void addStudent(const std::string& name, const std::string& email);
    void updateStudent(int id, const std::string& name, const std::string& email);
    void deleteStudent(int id);
    std::vector<Student> getStudents();
    std::vector<Student> filterStudentsByName(const std::string& name);
    std::vector<Student> sortStudentsByName(bool ascending = true);

    // Subject operations
    void addSubject(const std::string& name);
    std::vector<Subject> getSubjects();

    // Grade operations
    void addGrade(int student_id, int subject_id, float grade);
    void updateGrade(int grade_id, float grade);
    void deleteGrade(int grade_id);
    std::vector<Grade> getGrades();
    std::vector<Grade> filterGradesByValue(float min_grade, float max_grade);
    std::vector<Grade> sortGradesByValue(bool ascending = true);
};

#endif
