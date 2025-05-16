Application de Gestion des Étudiants
Description
L'Application de Gestion des Étudiants est un projet développé en C++ utilisant le framework Qt pour l'interface graphique et MySQL Connector/C++ pour la gestion de la base de données. Ce projet permet de gérer les informations des étudiants, des matières et des notes avec des fonctionnalités telles que l'ajout, la modification, la suppression, le filtrage et le tri des données. La base de données est hébergée localement via XAMPP.
Ce projet a été conçu dans le cadre d'un travail académique pour démontrer l'utilisation de la programmation orientée objet, des interfaces graphiques et de la gestion de bases de données relationnelles.
Fonctionnalités

Gestion des étudiants : Ajouter, modifier, supprimer et lister les étudiants (ID, nom, email).
Gestion des matières : Ajouter et lister les matières (ID, nom).
Gestion des notes : Ajouter et lister les notes (ID, étudiant, matière, note).
Filtrage : Filtrer les étudiants par nom.
Interface graphique : Interface Qt avec tableau pour afficher les données et boutons pour les opérations CRUD.
Base de données : Stockage des données dans une base MySQL (student_management).

Prérequis

Système d'exploitation : Windows (testé sur Windows 10/11).
XAMPP : Pour exécuter le serveur MySQL localement.
Qt : Version 6.2.4 ou supérieure avec MinGW 64 bits (installé à C:\Qt\6.2.4\mingw81_64).
MySQL Connector/C++ : Version 9.3.0 (extrait à C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64\mysql-connector-c++-9.3.0-winx64).
Compilateur : MinGW 64 bits (fourni avec Qt).
IDE : Qt Creator (recommandé) ou VS Code pour l'édition.

Structure du Projet
pfm c++/
├── include/                    # Fichiers d'en-tête C++
│   ├── student.h
│   ├── subject.h
│   ├── grade.h
│   ├── database_manager.h
│   ├── mainwindow.h
├── src/                        # Fichiers source C++
│   ├── student.cpp
│   ├── subject.cpp
│   ├── grade.cpp
│   ├── database_manager.cpp
│   ├── mainwindow.cpp
│   ├── main.cpp
├── sql/                        # Scripts SQL
│   ├── create_database.sql
├── ui/                         # Fichiers d'interface Qt (optionnel)
│   ├── mainwindow.ui
├── resources/                  # Ressources Qt
│   ├── app.qrc
├── docs/                       # Documentation
│   ├── livrable.pdf
│   ├── presentation.pdf
│   ├── diagrams/
├── build/                      # Sortie de compilation
│   ├── student_management.exe
├── student_management.pro      # Fichier projet Qt
└── README.md                   # Ce fichier

Installation
1. Installer les Dépendances
XAMPP

Téléchargez et installez XAMPP depuis apachefriends.org.
Lancez le panneau de contrôle XAMPP et démarrez MySQL.

Qt

Téléchargez l'installateur Qt depuis qt.io.
Installez Qt 6.2.4 (ou version récente) avec MinGW 64 bits à C:\Qt.
Incluez Qt Creator pour faciliter le développement.

MySQL Connector/C++

Téléchargez mysql-connector-c++-9.3.0-winx64.zip depuis dev.mysql.com.
Extrayez à C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64.
Copiez les DLL nécessaires :copy "C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64\mysql-connector-c++-9.3.0-winx64\lib64\mysqlcppconn-10-vs14.dll" "build"
copy "C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64\mysql-connector-c++-9.3.0-winx64\lib64\libcrypto-3-x64.dll" "build"
copy "C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64\mysql-connector-c++-9.3.0-winx64\lib64\libssl-3-x64.dll" "build"



2. Configurer la Base de Données

Ouvrez phpMyAdmin (http://localhost/phpmyadmin) via XAMPP.
Exécutez le script SQL pour créer la base student_management :mysql -u root -p < sql/create_database.sql

Ou importez sql/create_database.sql dans phpMyAdmin.

3. Configurer le Projet
Avec Qt Creator

Ouvrez student_management.pro dans Qt Creator.
Configurez avec le kit MinGW 64 bits (par exemple, C:\Qt\6.2.4\mingw81_64).
Compilez (Ctrl+B) et exécutez (Ctrl+R).

Avec la Ligne de Commande

Ajoutez Qt au PATH :set PATH=%PATH%;C:\Qt\6.2.4\mingw81_64\bin


Naviguez vers le répertoire du projet :cd C:\Users\ycode\Desktop\pfm c++


Générez le Makefile :qmake student_management.pro


Compilez :mingw32-make


Exécutez :.\build\student_management.exe



4. Configurer VS Code (Optionnel)
Si vous utilisez VS Code pour l'édition :

Mettez à jour .vscode/c_cpp_properties.json pour IntelliSense :{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/include",
                "C:/Users/ycode/Downloads/mysql-connector-c++-9.3.0-winx64/mysql-connector-c++-9.3.0-winx64/include",
                "C:/Qt/6.2.4/mingw81_64/include",
                "C:/Qt/6.2.4/mingw81_64/include/QtCore",
                "C:/Qt/6.2.4/mingw81_64/include/QtGui",
                "C:/Qt/6.2.4/mingw81_64/include/QtWidgets"
            ],
            "defines": ["_DEBUG", "UNICODE", "_UNICODE"],
            "compilerPath": "C:/Qt/6.2.4/mingw81_64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}


Redémarrez VS Code.

Utilisation

Lancez l'application (.\build\student_management.exe).
L'interface Qt affiche un tableau des étudiants.
Utilisez les boutons pour :
Ajouter un étudiant : Saisissez nom et email.
Actualiser : Mettre à jour le tableau.
(Fonctionnalités supplémentaires comme modifier/supprimer peuvent être ajoutées en étendant mainwindow.cpp.)


Vérifiez les modifications dans phpMyAdmin (student_management > students).

Documentation

Livrable : docs/livrable.pdf (3 pages, double colonne) décrit le projet, le schéma de la base de données, l'architecture, et l'implémentation.
Présentation : docs/presentation.pdf (10 diapositives) couvre les objectifs, le schéma, l'interface, et les défis.
Diagrammes :
docs/diagrams/er_diagram.png : Diagramme ER de la base de données.
docs/diagrams/class_diagram.png : Diagramme de classes C++.
docs/diagrams/gui_screenshot.png : Capture d'écran de l'interface.



Contribution

Clonez le dépôt :git clone <url_du_dépôt>


Créez une branche pour vos modifications :git checkout -b ma-fonctionnalité


Soumettez une pull request après avoir testé vos changements.

Problèmes Connus

Erreur "DLL manquante" : Vérifiez que les DLLs (mysqlcppconn-10-vs14.dll, etc.) sont dans build.
Erreur de connexion à la base de données : Assurez-vous que XAMPP MySQL est en cours d'exécution et que les identifiants dans database_manager.cpp sont corrects.
IntelliSense dans VS Code : Mettez à jour c_cpp_properties.json avec les chemins corrects.

Licence
Ce projet est sous licence MIT.
Auteurs:TAWBA ZEHAF


Contact
Pour toute question, contactez [tawbazehaf@gmail.com] ou ouvrez une issue sur GitHub.
