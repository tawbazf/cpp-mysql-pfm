#include "database_manager.h"
#include <stdexcept>

DatabaseManager::DatabaseManager() {
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("student_management");
    } catch (sql::SQLException& e) {
        throw std::runtime_error("Database connection failed: " + std::string(e.what()));
    }
}

DatabaseManager::~DatabaseManager() { delete con; }

void DatabaseManager::addStudent(const std::string& name, const std::string& email) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO students(name, email) VALUES (?, ?)"));
    pstmt->setString(1, name);
    pstmt->setString(2, email);
    pstmt->execute();
}

void DatabaseManager::addSubject(const std::string& name) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO subjects(name) VALUES (?)"));
    pstmt->setString(1, name);
    pstmt->execute();
}

void DatabaseManager::addGrade(int student_id, int subject_id, float grade) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO grades(student_id, subject_id, grade) VALUES (?, ?, ?)"));
    pstmt->setInt(1, student_id);
    pstmt->setInt(2, subject_id);
    pstmt->setDouble(3, grade);
    pstmt->execute();
}

void DatabaseManager::updateStudent(int id, const std::string& name, const std::string& email) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("UPDATE students SET name = ?, email = ? WHERE student_id = ?"));
    pstmt->setString(1, name);
    pstmt->setString(2, email);
    pstmt->setInt(3, id);
    pstmt->execute();
}

void DatabaseManager::deleteStudent(int id) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("DELETE FROM students WHERE student_id = ?"));
    pstmt->setInt(1, id);
    pstmt->execute();
}

std::vector<Student> DatabaseManager::getStudents() {
    std::vector<Student> students;
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM students"));
    while (res->next()) {
        students.emplace_back(res->getInt("student_id"), res->getString("name"),
                             res->getString("email"));
    }
    return students;
}

std::vector<Subject> DatabaseManager::getSubjects() {
    std::vector<Subject> subjects;
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM subjects"));
    while (res->next()) {
        subjects.emplace_back(res->getInt("subject_id"), res->getString("name"));
    }
    return subjects;
}

std::vector<Grade> DatabaseManager::getGrades() {
    std::vector<Grade> grades;
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM grades"));
    while (res->next()) {
        grades.emplace_back(res->getInt("grade_id"), res->getInt("student_id"),
                            res->getInt("subject_id"), res->getDouble("grade"));
    }
    return grades;
}

std::vector<Student> DatabaseManager::filterStudentsByName(const std::string& name) {
    std::vector<Student> students;
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT * FROM students WHERE name LIKE ?"));
    pstmt->setString(1, "%" + name + "%");
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    while (res->next()) {
        students.emplace_back(res->getInt("student_id"), res->getString("name"),
                             res->getString("email"));
    }
    return students;
}