# 🚀 Task Tracker CLI

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License">
  <img src="https://img.shields.io/badge/JSON-nlohmann%2Fjson-orange.svg" alt="nlohmann/json">
</p>

---

> **Project Source:** This project idea and requirements were inspired by [roadmap.sh Task Tracker Project](https://roadmap.sh/projects/task-tracker).

A simple, modern command-line task tracker written in C++ with JSON-based persistent storage. Effortlessly manage your tasks from the terminal with a clean and intuitive interface.

---

## ✨ Features
- ➕ Add new tasks with descriptions
- 👀 View all tasks with status and timestamps
- ✏️ Update or delete existing tasks
- 💾 Persistent storage using JSON

## 📦 Requirements
- C++17 compatible compiler (e.g., g++)
- [nlohmann/json](https://github.com/nlohmann/json) single-header library (included in `single_include/nlohmann/json.hpp`)

## 🛠️ Building
This project uses a Makefile. To build the CLI:

```sh
make
```

This will produce an executable named `task-cli`.

## 🚦 Usage
Run the CLI with the following commands:

- **View all tasks (default):**
  ```sh
  ./task-cli
  ./task-cli view
  ```
- **Add a new task:**
  ```sh
  ./task-cli add "Task description here"
  ```
- **Update a task:**
  ```sh
  ./task-cli update <task_number> "New description"
  ```
- **Delete a task:**
  ```sh
  ./task-cli delete <task_number>
  ```

## 🗂️ Data Format
Tasks are stored in `data.json` as a JSON object, with each task containing:
- `description`: Task description
- `status`: Task status (`todo`, `in_progress`, etc.)
- `date created`: Creation timestamp (epoch)
- `date updated`: Last update timestamp (epoch)

## 📁 Project Structure
```
├── Makefile                # Build instructions
├── main.cpp                # Main CLI source code
├── data.json               # Task data (auto-generated)
├── single_include/         # nlohmann/json single-header library
│   └── nlohmann/
│       └── json.hpp
└── .vscode/                # VS Code settings (optional)
```

## 📝 License
MIT (see nlohmann/json for its own license)
