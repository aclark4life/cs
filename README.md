# Computer Science Portfolio: 1995-1999

<img src="me.jpg" alt="Jeffrey 'Alex' Clark, 1998" width="481" />

This repository contains a collection of coursework, research projects, and experimental code from my undergraduate Computer Science studies (circa 1995-1999). It serves as a historical archive of my early journey into systems programming, data structures, and compiler construction.

The curriculum and course descriptions are based on the [Loyola University Maryland Computer Science major requirements (archived 1998)](https://web.archive.org/web/19980524213843/http://www.cs.loyola.edu/courses/major/).

## 🚀 Recent Maintenance & Refactoring (2026)

In April 2026, this repository underwent a "Capstone Refactoring" pass to bring the code into a professional maintenance mode.

**Co-authored with Gemini CLI:**
- **Codebase Professionalization:** Scrubbed informal comments and placeholder strings from lexers and data structures.
- **Structural Cleanup:** Renamed files and directories to follow professional naming conventions (e.g., `462/t/hello.c`, `462/f/stuff`).
- **Memory & Logic Improvements:** Ongoing efforts to address legacy memory leaks (Gauss-Jordan) and refactor complex legacy insertion logic (Sparse Matrices).
- **Modern Build Standards:** Unifying build processes and documentation.

---

## 📚 Curriculum & Projects

### 262: Programming and Data Structures
Continuation of foundational CS concepts including elementary file handling and abstract data types (lists, stacks, queues, and trees).
- **Featured Project:** A Sparse Matrix implementation using a 2D linked list (`262/list.c`).

### 295: Discrete Structures
Boolean algebra, combinatorics, graphs, inductive and deductive proofs, recurrences, and finite state machines.

### 301: Computational Linear Algebra
Implementation of numerical methods for linear systems.
- **Featured Project:** Gauss-Jordan elimination for solving MxN systems (`301/gauss/g.c`).

### 364: File and Data Structures
Advanced data organization and storage techniques.

### 366: Systems Level Programming
Low-level programming, including DOS device drivers and 16-bit Assembly games.
- **Featured Project:** A "Missile Command" style game written in x86 Assembly (`366/src/rocks.asm`).
- **Featured Project:** A dummy block device driver for DOS (`366/src/blkdrv.asm`).

### 420: Computer Science Research
Research in Software Construction Methods under Dr. Keith Gallagher. Surveyed development methodologies including clean-room and rapid prototyping.

### 451: Programming Languages
Comparative study of programming language paradigms.

### 461: Compiler Construction
Theory and practice of compiler design.
- **Featured Project:** A lexical analyzer using Flex/Lex (`461/project/prac/scan.l`).

### 462: Algorithm Analysis
Complexity analysis and advanced algorithmic strategies.

### 466: Operating Systems
Principles of OS design, process management, and networking.
- **Featured Project:** A custom Unix-like shell with redirection and piping support (`466/shell2/4/`).
- **Featured Project:** Socket-level network programming utilities (`466/tok/socket.c`).

---

## 📂 Directory Structure

```
.
├── 262 (Data Structures)
│   ├── list.c (Sparse Matrix)
│   └── ...
├── 301 (Linear Algebra)
│   ├── gauss/ (Gauss-Jordan Elimination)
│   └── ...
├── 366 (Systems Programming)
│   ├── src/ (x86 Assembly Projects)
│   └── ...
├── 461 (Compiler Construction)
│   ├── project/ (Lexer/Parser logic)
│   └── ...
├── 466 (Operating Systems)
│   ├── shell2/ (Custom Shell)
│   ├── tok/ (Socket Programming)
│   └── ...
└── README.md
```

---
*Archive maintained by Jeffrey 'Alex' Clark.*
