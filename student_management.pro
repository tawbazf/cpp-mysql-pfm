QT += core gui widgets
TARGET = student_management
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/student.cpp \
    src/subject.cpp \
    src/grade.cpp \
    src/database_manager.cpp

HEADERS += \
    include/mainwindow.h \
    include/student.h \
    include/subject.h \
    include/grade.h \
    include/database_manager.h

INCLUDEPATH += "C:/Users/ycode/Documents/mysql-connector-c++-9.3.0-winx64/mysql-connector-c++-9.3.0-winx64/include"
LIBS += -L"C:/Users/ycode/Documents/mysql-connector-c++-9.3.0-winx64/mysql-connector-c++-9.3.0-winx64/lib64" -lmysqlcppconn-10-vs14

RESOURCES += resources/app.qrc