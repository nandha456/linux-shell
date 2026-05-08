# 🐚 My-Shell

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

A minimal, high-performance command-line interpreter built from scratch in C. This project demonstrates core systems programming concepts including **process management**, **memory-efficient parsing**, and the **Linux lifecycle**.

---

## 🚀 Key Features

* **State-Aware Lexer**: A hand-written parser that handles single/double quotes and preserves spaces (e.g., `echo "hello world"` works perfectly).
* **Process Isolation**: Uses the `fork-exec` model. If a command crashes, the shell stays alive.
* **Built-in Logic**: Native support for `cd` and `exit` handled directly in the parent process.
* **Zero Latency**: Uses `fflush(stdout)` to ensure the prompt appears instantly without buffering delays.

---

## 🛠️ Architecture: How it Works

The shell operates on a **REPL** (Read-Evaluate-Print Loop) architecture:



1.  **Read**: Captures raw input using `fgets`.
2.  **Parse**: Converts the input string into a `char *args[]` vector using a pointer-based scanner.
3.  **Fork**: Clones the shell process to create a "sacrificial" child.
4.  **Exec**: The child process undergoes a "brain transplant" via `execvp`.
5.  **Wait**: The parent process reaps the child using `waitpid` to prevent zombie processes.

---

## 🚦 Getting Started

### Prerequisites
* Arch Linux (or any Linux distro)
* `gcc` & `make`

### Installation
```bash
# Clone the repository
git clone https://github.com/nandha456/linux-shell
cd myshell

# Build the project
make

# Run the shell
./myshell


#NOW YOUR IN YOUR CUSTOM SHELL
