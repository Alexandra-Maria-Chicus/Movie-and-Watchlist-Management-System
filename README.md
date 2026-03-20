# Movie and Watchlist Management System

[cite_start]A robust C++ desktop application designed to manage a personal movie library and curated watchlists[cite: 24, 25]. [cite_start]This project demonstrates the transition from a console-based logic to a modern graphical interface, emphasizing clean architecture and object-oriented principles[cite: 25, 26].

## 🚀 Features

* **Dual Interface**: Supports both a menu-driven console interface and a sophisticated Qt-based Graphical User Interface (GUI).
* **Library Management**: Comprehensive CRUD functionality to add, search, update, and delete movies from the database.
* **Personalized Watchlists**: Allows users to manage a custom list of movies they intend to watch.
* **Data Persistence**: Integrated storage systems to ensure movie information and user watchlists are maintained across different sessions[.
* **User Experience**: Focused on clear navigation, responsive UI components, and a consistent design language.

## 🛠️ Technical Stack

* **Language**: C++.
* **Framework**: Qt (for GUI development).
* **Methodology**: Object-Oriented Programming (OOP) and modular architecture.
* **Tools**: Git for version control, Visual Studio/CLion for development.

## 🏗️ Architecture

The system is built using a modular and extensible architecture:

1.  **Domain Layer**: Defines the Movie entity and core data structures.
2.  **Repository Layer**: Handles persistent data storage and retrieval.
3.  **Service Layer**: Implements the business logic for managing lists and search filters.
4.  **UI Layer**: Provides the interaction points through either the Command Line or the Qt Framework.
