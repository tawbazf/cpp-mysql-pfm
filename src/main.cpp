#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DatabaseManager db;
    MainWindow window(db);
    window.show();
    return app.exec();
}