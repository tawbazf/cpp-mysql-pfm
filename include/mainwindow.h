#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "database_manager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStudent();
    void updateStudent();
    void deleteStudent();
    void filterStudents();
    void sortStudentsByNameAsc();
    void sortStudentsByNameDesc();
    void addGrade();
    void updateGrade();
    void deleteGrade();
    void filterGrades();
    void sortGradesByValueAsc();
    void sortGradesByValueDesc();
    void refreshStudentsTable();
    void refreshGradesTable();

private:
    DatabaseManager dbManager;
    QTableWidget *tableWidget;
    void setupUI();
};

#endif