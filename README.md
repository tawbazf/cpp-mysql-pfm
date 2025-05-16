# Application de Gestion des Étudiants

## Description

L'**Application de Gestion des Étudiants** est un projet développé en **C++** utilisant **Qt** pour l'interface graphique et **MySQL Connector/C++** pour la gestion de la base de données.  
Elle permet de gérer les informations des étudiants, des matières et des notes avec des fonctionnalités telles que l'ajout, la modification, la suppression, le filtrage et le tri des données.  
La base de données est hébergée localement via **XAMPP**.

> Ce projet a été conçu dans le cadre d'un travail académique pour démontrer l'utilisation de la programmation orientée objet, des interfaces graphiques et de la gestion de bases de données relationnelles.

## Fonctionnalités

- **Gestion des étudiants** : Ajouter, modifier, supprimer et lister les étudiants (ID, nom, email).
- **Gestion des matières** : Ajouter et lister les matières (ID, nom).
- **Gestion des notes** : Ajouter et lister les notes (ID, étudiant, matière, note).
- **Filtrage** : Filtrer les étudiants par nom.
- **Interface graphique** : Interface Qt avec tableaux et boutons pour les opérations CRUD.
- **Base de données** : Stockage MySQL (base `student_management`).

## Prérequis

- **Système** : Windows 10/11
- **XAMPP** : Serveur MySQL local
- **Qt** : Version ≥ 6.2.4 (avec MinGW 64 bits)
- **MySQL Connector/C++** : Version 9.3.0
- **Compilateur** : MinGW 64 bits (fourni avec Qt)
- **IDE** : Qt Creator recommandé (ou VS Code)

## Structure du Projet
pfm/
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

## Installation

### 1. Installer les Dépendances

#### XAMPP
- Télécharger XAMPP depuis https://www.apachefriends.org
- Lancer MySQL via le panneau de contrôle

#### Qt
- Télécharger depuis https://www.qt.io/download
- Installer Qt 6.2.4 avec MinGW 64 bits (ex: `C:\Qt\6.2.4\mingw81_64`)

#### MySQL Connector/C++
- Télécharger `mysql-connector-c++-9.3.0-winx64.zip` depuis https://dev.mysql.com
- Extraire dans `C:\Users\ycode\Downloads\mysql-connector-c++-9.3.0-winx64`
- Copier les DLL nécessaires dans `build/` :
  ```bash
  copy "...\lib64\mysqlcppconn-10-vs14.dll" build
  copy "...\lib64\libcrypto-3-x64.dll" build
  copy "...\lib64\libssl-3-x64.dll" build
2. Configurer la Base de Données
Ouvrir phpMyAdmin : http://localhost/phpmyadmin

Exécuter le script SQL :
mysql -u root -p < sql/create_database.sql
Ou importer manuellement sql/create_database.sql via l’interface phpMyAdmin.
3. Configurer le Projet
Avec Qt Creator
Ouvrir student_management.pro

Sélectionner le kit MinGW (ex: C:\Qt\6.2.4\mingw81_64)

Compiler (Ctrl+B) et exécuter (Ctrl+R)

Avec la Ligne de Commande
set PATH=%PATH%;C:\Qt\6.2.4\mingw81_64\bin
cd "C:\Users\ycode\Desktop\pfm c++"
qmake student_management.pro
mingw32-make
.\build\student_management.exe
4. Configurer VS Code (Optionnel)
Fichier .vscode/c_cpp_properties.json :
{
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "${workspaceFolder}/include",
        "C:/Users/ycode/Downloads/mysql-connector-c++-9.3.0-winx64/include",
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
Utilisation
Lancer l'exécutable : .\build\student_management.exe

Interface Qt avec :

Ajouter un étudiant (nom, email)

Actualiser la liste

(Modification / suppression disponibles en étendant mainwindow.cpp)

Vérification possible via phpMyAdmin : student_management > students

Documentation
Livrable : docs/livrable.pdf – description du projet, base de données, architecture

Présentation : docs/presentation.pdf – objectifs, interface, défis

Diagrammes :

docs/diagrams/er_diagram.png – Diagramme ER

docs/diagrams/class_diagram.png – Diagramme de classes C++

docs/diagrams/gui_screenshot.png – Interface graphique
Contribution
git clone https://github.com/tawbazf/cpp-mysql-pfm.git
git checkout -b ma-fonctionnalité
# Développez, testez puis :
# Ouvrez une pull request
Problèmes Connus
DLL manquante : Vérifiez que les fichiers .dll sont présents dans build/

Connexion échouée : Assurez-vous que MySQL est actif et que database_manager.cpp contient les bons identifiants

VS Code IntelliSense : Vérifiez les chemins dans .vscode/c_cpp_properties.json

Licence
Ce projet est sous licence MIT.
Auteurs
TAWBA ZEHAF

Contact
Email : tawbazehaf@gmail.com

Ou ouvrez une issue sur GitHub.

