#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    int id;
    std::string name;
    std::string email;
    Student(int id, std::string name, std::string email) : id(id), name(name), email(email) {}
};

#endif