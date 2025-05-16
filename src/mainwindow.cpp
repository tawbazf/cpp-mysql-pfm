#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), tableWidget(new QTableWidget(this)) {
    try {
        setupUI();
        refreshStudentsTable();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Initialisation échouée : ") + e.what());
    }
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Table setup
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"ID", "Nom/Étudiant ID", "Email/Matière ID", "Note"});
    mainLayout->addWidget(tableWidget);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    QPushButton *addStudentBtn = new QPushButton("Ajouter Étudiant", this);
    QPushButton *updateStudentBtn = new QPushButton("Modifier Étudiant", this);
    QPushButton *deleteStudentBtn = new QPushButton("Supprimer Étudiant", this);
    QPushButton *filterStudentsBtn = new QPushButton("Filtrer Étudiants", this);
    QPushButton *sortStudentsAscBtn = new QPushButton("Trier Nom (Croissant)", this);
    QPushButton *sortStudentsDescBtn = new QPushButton("Trier Nom (Décroissant)", this);
    QPushButton *addGradeBtn = new QPushButton("Ajouter Note", this);
    QPushButton *updateGradeBtn = new QPushButton("Modifier Note", this);
    QPushButton *deleteGradeBtn = new QPushButton("Supprimer Note", this);
    QPushButton *filterGradesBtn = new QPushButton("Filtrer Notes", this);
    QPushButton *sortGradesAscBtn = new QPushButton("Trier Notes (Croissant)", this);
    QPushButton *sortGradesDescBtn = new QPushButton("Trier Notes (Décroissant)", this);
    QPushButton *refreshStudentsBtn = new QPushButton("Afficher Étudiants", this);
    QPushButton *refreshGradesBtn = new QPushButton("Afficher Notes", this);

    buttonLayout->addWidget(addStudentBtn);
    buttonLayout->addWidget(updateStudentBtn);
    buttonLayout->addWidget(deleteStudentBtn);
    buttonLayout->addWidget(filterStudentsBtn);
    buttonLayout->addWidget(sortStudentsAscBtn);
    buttonLayout->addWidget(sortStudentsDescBtn);
    buttonLayout->addWidget(addGradeBtn);
    buttonLayout->addWidget(updateGradeBtn);
    buttonLayout->addWidget(deleteGradeBtn);
    buttonLayout->addWidget(filterGradesBtn);
    buttonLayout->addWidget(sortGradesAscBtn);
    buttonLayout->addWidget(sortGradesDescBtn);
    buttonLayout->addWidget(refreshStudentsBtn);
    buttonLayout->addWidget(refreshGradesBtn);

    mainLayout->addLayout(buttonLayout);

    // Connect buttons to slots
    connect(addStudentBtn, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(updateStudentBtn, &QPushButton::clicked, this, &MainWindow::updateStudent);
    connect(deleteStudentBtn, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    connect(filterStudentsBtn, &QPushButton::clicked, this, &MainWindow::filterStudents);
    connect(sortStudentsAscBtn, &QPushButton::clicked, this, &MainWindow::sortStudentsByNameAsc);
    connect(sortStudentsDescBtn, &QPushButton::clicked, this, &MainWindow::sortStudentsByNameDesc);
    connect(addGradeBtn, &QPushButton::clicked, this, &MainWindow::addGrade);
    connect(updateGradeBtn, &QPushButton::clicked, this, &MainWindow::updateGrade);
    connect(deleteGradeBtn, &QPushButton::clicked, this, &MainWindow::deleteGrade);
    connect(filterGradesBtn, &QPushButton::clicked, this, &MainWindow::filterGrades);
    connect(sortGradesAscBtn, &QPushButton::clicked, this, &MainWindow::sortGradesByValueAsc);
    connect(sortGradesDescBtn, &QPushButton::clicked, this, &MainWindow::sortGradesByValueDesc);
    connect(refreshStudentsBtn, &QPushButton::clicked, this, &MainWindow::refreshStudentsTable);
    connect(refreshGradesBtn, &QPushButton::clicked, this, &MainWindow::refreshGradesTable);
}

void MainWindow::addStudent() {
    bool ok;
    QString name = QInputDialog::getText(this, "Ajouter Étudiant", "Nom:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        QString email = QInputDialog::getText(this, "Ajouter Étudiant", "Email:", QLineEdit::Normal, "", &ok);
        if (ok && !email.isEmpty()) {
            try {
                dbManager.addStudent(name.toStdString(), email.toStdString());
                refreshStudentsTable();
                QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès !");
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Erreur", QString("Échec de l'ajout de l'étudiant : ") + e.what());
            }
        }
    }
}

void MainWindow::updateStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Modifier Étudiant", "ID de l'étudiant:", 0, 0, 10000, 1, &ok);
    if (ok) {
        QString name = QInputDialog::getText(this, "Modifier Étudiant", "Nouveau nom:", QLineEdit::Normal, "", &ok);
        if (ok && !name.isEmpty()) {
            QString email = QInputDialog::getText(this, "Modifier Étudiant", "Nouvel email:", QLineEdit::Normal, "", &ok);
            if (ok && !email.isEmpty()) {
                try {
                    dbManager.updateStudent(id, name.toStdString(), email.toStdString());
                    refreshStudentsTable();
                    QMessageBox::information(this, "Succès", "Étudiant modifié avec succès !");
                } catch (const std::exception& e) {
                    QMessageBox::critical(this, "Erreur", QString("Échec de la modification : ") + e.what());
                }
            }
        }
    }
}

void MainWindow::deleteStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Supprimer Étudiant", "ID de l'étudiant:", 0, 0, 10000, 1, &ok);
    if (ok) {
        try {
            dbManager.deleteStudent(id);
            refreshStudentsTable();
            QMessageBox::information(this, "Succès", "Étudiant supprimé avec succès !");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Erreur", QString("Échec de la suppression : ") + e.what());
        }
    }
}

void MainWindow::filterStudents() {
    bool ok;
    QString name = QInputDialog::getText(this, "Filtrer Étudiants", "Nom (partiel):", QLineEdit::Normal, "", &ok);
    if (ok) {
        try {
            auto students = dbManager.filterStudentsByName(name.toStdString());
            tableWidget->setRowCount(0);
            tableWidget->setColumnCount(3);
            tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Email"});
            for (const auto& student : students) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);
                tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(student.getId())));
                tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(student.getName())));
                tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(student.getEmail())));
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Erreur", QString("Échec du filtrage : ") + e.what());
        }
    }
}

void MainWindow::sortStudentsByNameAsc() {
    try {
        auto students = dbManager.sortStudentsByName(true);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(3);
        tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Email"});
        for (const auto& student : students) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(student.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(student.getName())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(student.getEmail())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du tri : ") + e.what());
    }
}

void MainWindow::sortStudentsByNameDesc() {
    try {
        auto students = dbManager.sortStudentsByName(false);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(3);
        tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Email"});
        for (const auto& student : students) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(student.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(student.getName())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(student.getEmail())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du tri : ") + e.what());
    }
}

void MainWindow::addGrade() {
    bool ok;
    int student_id = QInputDialog::getInt(this, "Ajouter Note", "ID de l'étudiant:", 0, 0, 10000, 1, &ok);
    if (ok) {
        int subject_id = QInputDialog::getInt(this, "Ajouter Note", "ID de la matière:", 0, 0, 10000, 1, &ok);
        if (ok) {
            float grade = QInputDialog::getDouble(this, "Ajouter Note", "Note (0-20):", 0, 0, 20, 2, &ok);
            if (ok) {
                try {
                    dbManager.addGrade(student_id, subject_id, grade);
                    refreshGradesTable();
                    QMessageBox::information(this, "Succès", "Note ajoutée avec succès !");
                } catch (const std::exception& e) {
                    QMessageBox::critical(this, "Erreur", QString("Échec de l'ajout de la note : ") + e.what());
                }
            }
        }
    }
}

void MainWindow::updateGrade() {
    bool ok;
    int grade_id = QInputDialog::getInt(this, "Modifier Note", "ID de la note:", 0, 0, 10000, 1, &ok);
    if (ok) {
        float grade = QInputDialog::getDouble(this, "Modifier Note", "Nouvelle note (0-20):", 0, 0, 20, 2, &ok);
        if (ok) {
            try {
                dbManager.updateGrade(grade_id, grade);
                refreshGradesTable();
                QMessageBox::information(this, "Succès", "Note modifiée avec succès !");
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Erreur", QString("Échec de la modification : ") + e.what());
            }
        }
    }
}

void MainWindow::deleteGrade() {
    bool ok;
    int grade_id = QInputDialog::getInt(this, "Supprimer Note", "ID de la note:", 0, 0, 10000, 1, &ok);
    if (ok) {
        try {
            dbManager.deleteGrade(grade_id);
            refreshGradesTable();
            QMessageBox::information(this, "Succès", "Note supprimée avec succès !");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Erreur", QString("Échec de la suppression : ") + e.what());
        }
    }
}

void MainWindow::filterGrades() {
    bool ok;
    float min_grade = QInputDialog::getDouble(this, "Filtrer Notes", "Note minimale:", 0, 0, 20, 2, &ok);
    if (ok) {
        float max_grade = QInputDialog::getDouble(this, "Filtrer Notes", "Note maximale:", min_grade, 0, 20, 2, &ok);
        if (ok) {
            try {
                auto grades = dbManager.filterGradesByValue(min_grade, max_grade);
                tableWidget->setRowCount(0);
                tableWidget->setColumnCount(4);
                tableWidget->setHorizontalHeaderLabels({"ID", "Étudiant ID", "Matière ID", "Note"});
                for (const auto& grade : grades) {
                    int row = tableWidget->rowCount();
                    tableWidget->insertRow(row);
                    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(grade.getId())));
                    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(grade.getStudentId())));
                    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(grade.getSubjectId())));
                    tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(grade.getGrade())));
                }
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Erreur", QString("Échec du filtrage : ") + e.what());
            }
        }
    }
}

void MainWindow::sortGradesByValueAsc() {
    try {
        auto grades = dbManager.sortGradesByValue(true);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderLabels({"ID", "Étudiant ID", "Matière ID", "Note"});
        for (const auto& grade : grades) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(grade.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(grade.getStudentId())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(grade.getSubjectId())));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(grade.getGrade())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du tri : ") + e.what());
    }
}

void MainWindow::sortGradesByValueDesc() {
    try {
        auto grades = dbManager.sortGradesByValue(false);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderLabels({"ID", "Étudiant ID", "Matière ID", "Note"});
        for (const auto& grade : grades) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(grade.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(grade.getStudentId())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(grade.getSubjectId())));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(grade.getGrade())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du tri : ") + e.what());
    }
}

void MainWindow::refreshStudentsTable() {
    try {
        auto students = dbManager.getStudents();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(3);
        tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Email"});
        for (const auto& student : students) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(student.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(student.getName())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(student.getEmail())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec de l'actualisation : ") + e.what());
    }
}

void MainWindow::refreshGradesTable() {
    try {
        auto grades = dbManager.getGrades();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderLabels({"ID", "Étudiant ID", "Matière ID", "Note"});
        for (const auto& grade : grades) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(grade.getId())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(grade.getStudentId())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(grade.getSubjectId())));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(grade.getGrade())));
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec de l'actualisation : ") + e.what());
    }
}