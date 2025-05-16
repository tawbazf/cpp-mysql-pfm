#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int id;
    std::string name;
    std::string email;

public:
    Student(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
};

#endif