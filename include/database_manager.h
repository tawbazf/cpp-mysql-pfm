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

    void addStudent(const std::string& name, const std::string& email);
    void addSubject(const std::string& name);
    void addGrade(int student_id, int subject_id, float grade);
    void updateStudent(int id, const std::string& name, const std::string& email);
    void deleteStudent(int id);
    std::vector<Student> getStudents();
    std::vector<Subject> getSubjects();
    std::vector<Grade> getGrades();
    std::vector<Student> filterStudentsByName(const std::string& name);
};

#endif