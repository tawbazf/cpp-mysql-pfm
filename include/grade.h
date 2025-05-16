#ifndef GRADE_H
#define GRADE_H

class Grade {
public:
    int grade_id;
    int student_id;
    int subject_id;
    float grade;
    Grade(int grade_id, int student_id, int subject_id, float grade)
        : grade_id(grade_id), student_id(student_id), subject_id(subject_id), grade(grade) {}
};

#endif