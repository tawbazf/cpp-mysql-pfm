#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
private:
    int id;
    std::string name;

public:
    Subject(int id, const std::string& name) : id(id), name(name) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
};

#endif