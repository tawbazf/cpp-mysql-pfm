#include "mainwindow.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(DatabaseManager& db, QWidget *parent)
    : QMainWindow(parent), dbManager(db) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Email"});
    layout->addWidget(tableWidget);

    addButton = new QPushButton("Add Student", this);
    layout->addWidget(addButton);

    QPushButton *refreshButton = new QPushButton("Refresh", this);
    layout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addStudent);

    refreshTable();
}

void MainWindow::refreshTable() {
    tableWidget->setRowCount(0);
    std::vector<Student> students = dbManager.getStudents();
    tableWidget->setRowCount(students.size());
    for (size_t i = 0; i < students.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(students[i].id)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(students[i].name)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(students[i].email)));
    }
}

void MainWindow::addStudent() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Student", "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        QString email = QInputDialog::getText(this, "Add Student", "Email:", QLineEdit::Normal, "", &ok);
        if (ok && !email.isEmpty()) {
            try {
                dbManager.addStudent(name.toStdString(), email.toStdString());
                refreshTable();
                QMessageBox::information(this, "Success", "Student added successfully!");
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Failed to add student: ") + e.what());
            }
        }
    }
}