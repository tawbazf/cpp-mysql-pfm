#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database_manager.h"

class QTableWidget;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(DatabaseManager& db, QWidget *parent = nullptr);

private slots:
    void refreshTable();
    void addStudent();

private:
    DatabaseManager& dbManager;
    QTableWidget* tableWidget;
    QPushButton* addButton;
};

#endif