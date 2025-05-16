#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
public:
    int id;
    std::string name;
    Subject(int id, std::string name) : id(id), name(name) {}
};

#endif