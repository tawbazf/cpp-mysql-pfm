#ifndef GRADE_H
#define GRADE_H

class Grade {
private:
    int id;
    int student_id;
    int subject_id;
    float grade;

public:
    Grade(int id, int student_id, int subject_id, float grade)
        : id(id), student_id(student_id), subject_id(subject_id), grade(grade) {}
    int getId() const { return id; }
    int getStudentId() const { return student_id; }
    int getSubjectId() const { return subject_id; }
    float getGrade() const { return grade; }
};

#endif