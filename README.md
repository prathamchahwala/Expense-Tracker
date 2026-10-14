# 💰 Expense Tracker — C++

A simple, menu-driven **Expense Tracker built with C++** to manage your budget, record daily expenses, and monitor your remaining balance. This project demonstrates core C++ programming concepts and object-oriented programming through a practical command-line application.

<p align="center">
  <strong>Built with C++ | Command-Line Interface | File Handling</strong>
</p>

---

## 📌 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Technology Stack](#-technology-stack)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [How to Use](#-how-to-use)
- [Core Concepts](#-core-concepts)
- [Future Improvements](#-future-improvements)
- [Author](#-author)

---

## 🎯 Overview

Managing personal expenses is an important part of financial planning. The **Expense Tracker** provides a simple way to record spending, manage a budget, and check how much money remains available.

The application runs in the terminal and provides an interactive menu for managing budget and expense records. It also saves data locally so that previously recorded information can be loaded in subsequent sessions.

### 🎯 Project Objectives

- Develop a practical application using C++.
- Apply object-oriented programming concepts.
- Understand file handling and data persistence.
- Practise functions, program structure, and input handling.
- Build a foundation for more advanced financial management applications.

---

## ✨ Features

- **💵 Budget Management** — Add a budget and keep track of available funds.
- **📝 Expense Recording** — Record expenses with details such as date, description, and amount.
- **📊 Expense Overview** — View recorded expenses and monitor spending.
- **💰 Remaining Balance** — Check the remaining budget after expenses.
- **💾 Data Persistence** — Save and load records using local file storage.
- **🗑️ Data Reset** — Clear saved budget and expense information when required.
- **🖥️ Interactive CLI** — Navigate through the application using a menu-driven interface.

---

## 🛠️ Technology Stack

| Technology | Purpose |
|---|---|
| C++ | Core programming language |
| Standard C++ Library | Input, output, and general programming utilities |
| File Handling | Saving and loading application data |
| Object-Oriented Programming | Organizing application logic and data |
| Terminal / Command Line | User interaction |

---

## 📂 Project Structure

The repository is organized into source code and header files:

```text
Expense-Tracker/
│
├── include/             # Header files
├── src/                 # C++ source files
├── .github/             # GitHub templates and configuration
├── .gitignore           # Files excluded from version control
└── README.md            # Project documentation
```

The application uses `data.txt` for local data storage, as described in the application instructions. The file may be created when the application runs.

---

## 🚀 Getting Started

Follow these steps to download, compile, and run the project locally.

### Prerequisites

Make sure you have:

- A C++ compiler such as **GCC (g++)**.
- Git installed on your computer.
- A terminal or command-line environment.

### 1. Clone the Repository

```bash
git clone https://github.com/prathamchahwala/Expense-Tracker.git
```

### 2. Navigate to the Project

```bash
cd Expense-Tracker
```

### 3. Compile the Program

Run the following command from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -I include src/*.cpp -o Expense_Tracker
```

This command compiles the C++ source files and creates an executable named `Expense_Tracker`.

### 4. Run the Application

**Linux / macOS / compatible terminals:**

```bash
./Expense_Tracker
```

**Windows Command Prompt:**

```cmd
Expense_Tracker.exe
```

If your compiler or terminal does not support the source-file wildcard, compile the source files individually by specifying their filenames.

---

## 📖 How to Use

1. Launch the application.
2. Follow the options displayed in the main menu.
3. Add your budget amount.
4. Record expenses using the information requested by the program.
5. View your recorded expenses and remaining budget.
6. Clear your saved information if you want to reset the tracker.

Your saved information can be loaded again during subsequent runs, provided the data file remains available in the expected location.

---

## 🧠 Core Concepts

This project provides practical experience with the following programming concepts:

- **C++ fundamentals:** variables, data types, operators, and control statements.
- **Functions:** separating tasks into manageable operations.
- **Object-oriented programming:** organizing data and behaviour into appropriate classes.
- **File handling:** reading and writing persistent records.
- **Input/output:** interacting with users through the terminal.
- **Program organization:** separating declarations, implementations, and application logic.

---

## 🔮 Future Improvements

The following enhancements could make the project more powerful:

- [ ] Categorize expenses, such as food, travel, education, and shopping.
- [ ] Add monthly and yearly expense summaries.
- [ ] Display category-wise spending reports.
- [ ] Implement date-based expense filtering.
- [ ] Add budget alerts when spending approaches a limit.
- [ ] Export expense records to CSV.
- [ ] Introduce a database such as SQLite.
- [ ] Develop a graphical user interface.
- [ ] Add automated tests and improved error handling.

---

## 👨‍💻 Author

**Pratham Chahwala**

Computer Science / Engineering Student | Aspiring Software Engineer

- **GitHub:** [@prathamchahwala](https://github.com/prathamchahwala)
- **Project Repository:** [Expense-Tracker](https://github.com/prathamchahwala/Expense-Tracker)

---

## ⭐ Support

If you find this project useful, consider giving the repository a ⭐ on GitHub.

Suggestions, feedback, and contributions that help improve the project are welcome.

---

<p align="center">
  <strong>Built with ❤️ using C++</strong>
</p>
