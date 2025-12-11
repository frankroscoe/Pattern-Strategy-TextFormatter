# Pattern-Strategy-TextFormatter

> Teaching artifact and portfolio demo: Strategy Design Pattern in C++ with UML clarity.

---

## Overview
This repository demonstrates the **Strategy Design Pattern** implemented in C++.  
The example focuses on a **TextFormatter** context, where different formatting strategies (e.g., uppercase, lowercase, or custom rules) can be applied interchangeably at runtime.

The project is designed as a **teaching artifact** and portfolio piece, showing both:
- Clean C++ implementation of the Strategy Pattern.
- Supporting UML diagrams for design clarity.
- Recruiter‑friendly documentation and reproducible workflow.

---

## Current State
- **Single-file implementation** (`TextFormatter.cpp`) for simplicity and clarity.
- UML artifacts included in `/docs`:
  - Class diagram (`.png`, `.pdf`)
  - Editable UML (`.uxf`)
- `.gitignore` configured to exclude build outputs and Visual Studio artifacts.

---

## Roadmap
Future updates will:
- **Decompose** the single `.cpp` file into header (`.h`) and source (`.cpp`) files for best practices.
- Add **unit tests** to demonstrate strategy switching.
- Expand documentation with more design pattern examples.

---

## Repository Structure

    Pattern-Strategy-TextFormatter/
    ├── src/
    │   └── TextFormatter.cpp        # Strategy Pattern demo (single-file version)
    ├── docs/
    │   ├── Pattern-Strategy-TextFormatter-UML-ClassDiagram.png
    │   ├── Pattern-Strategy-TextFormatter-UML-ClassDiagram.pdf
    │   └── Pattern-Strategy-TextFormatter-UML-ClassDiagram.uxf
    └── .gitignore

---

## How to Build
### Prerequisites
- Install a C++ compiler such as **g++** (available via GCC on Linux/macOS, or MinGW/WSL on Windows).
- Alternatively, you may use **Visual Studio** on Windows.

### Option 1: Using g++ (recommended, cross-platform)
1. Compile the source file:
 
       g++ src/TextFormatter.cpp -o TextFormatterDemo
       
2. Run the demo:

       ./TextFormatterDemo

### Option 2: Using Visual Studio (Windows only)
1. Open the solution in **Visual Studio**.
2. Build the project (Ctrl+Shift+B).
3. Run the executable from the **Debug** or **Release** folder.

---

## Educational Notes
- This repo models **professional Git workflow discipline**:
  - Clean commit history.
  - Recruiter‑friendly documentation.
  - UML artifacts for teaching clarity.
- Intended for **students, educators, and recruiters** to see both code and design rationale.

---

## License
This project is licensed under the [MIT License](LICENSE).  
It is intended as a learning resource—feel free to explore the code and artifacts.
