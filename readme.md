# 🎄 Advent of Code 2025 Solutions (Gurjaka) - C Implementation

This repository contains my solutions for the [Advent of Code 2025](https://adventofcode.com/) programming puzzles, implemented primarily in **C**.

Given C's capabilities, the core principles guiding these solutions are:

1.  **Correctness:** Functional, reliable logic for both parts of every puzzle.
2.  **Performance & Low-Level Control:** Solutions are designed to be optimally performant. This means careful memory management, efficient pointer use, and targeting the best possible **Time Complexity** (Big O Notation).
3.  **Clarity & Abstraction:** Even in C, the code must be clean, modular, and well-documented to explain complex algorithms.

---

## 🏗 Project Structure & Build

Each day resides in its own directory (`dayXX`). The solutions are compiled individually, typically linking against a common utility library for basic file I/O or string parsing if necessary.

### Directory Layout
```ruby
├── day01/
│   ├── day01.c           # Main solution file (Part 1 and Part 2)
│   ├── input.txt         # The specific puzzle input for the day
│   └── readme.md         # File containing the puzzle
├── day02/
│   └── ...
├── include/
│   └── day01.h           # Header for any function prototypes
│   └── ...
└── README.md
```

### Building and Running

The solutions are designed to be built using a standard compiler like `gcc` or `clang`.

To build **all programs**, simply run:

```bash
make
````


**The Makefile includes a special target `generate_day`:**

```bash
make generate_day
```

This will:

* Compile `generate_day.c` into `.build/generate_day.o`
* Link it into the `generate_day` executable

**To remove all build files and executables:**

```bash
make clean
```

This will delete:

* `.build/` directory
* All `day*/main` executables
* The `generate_day` executable

---
