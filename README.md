# 🏔️ StayNear — Student PG Accommodation System
> **Object-Oriented Programming (OOP) in C++ (College / University Project)**

---

## 📌 1. Project Overview
**StayNear** is a student paying-guest (PG) accommodation and bed tracking system designed for college students in Bhimtal, Uttarakhand (e.g., students of **GEHU Bhimtal** and **BIAS Bhimtal**). 

The project allows students and administrators to:
1. **Browse & Filter PGs**: Filter by monthly budget, accommodation type (Boys / Girls / Co-Ed), and nearby college.
2. **Track Bed Availability**: Real-time monitoring of total beds, occupied beds, and available beds across all rooms.
3. **Register New PGs**: Input PG details, room configurations, and owner contact information.
4. **Inspect Room Occupancy**: View individual rooms and the students staying in each bed.
5. **Dual Mode Support**:
   - **Interactive Console CLI Mode** (Pure standard C++, runs anywhere in terminal).
   - **Modern Qt 6 Desktop GUI** (Dark-themed desktop application with search filters, stat cards, and tree view).

---

## 📁 2. Wise & Clean File Organization

All source files are organized into logical modules so you and your teacher can navigate the project easily:

```text
StayNear/
├── CMakeLists.txt                 # Master CMake build script for CLI & GUI targets
├── README.md                      # Complete viva & teacher explanation guide
│
├── src/
│   ├── models/                    # [DATA MODELS] Core OOP classes
│   │   ├── Person.h / .cpp        # Base class (Inheritance base)
│   │   ├── Student.h / .cpp       # Derived class (Student IS-A Person)
│   │   ├── Owner.h / .cpp         # Derived class (Owner IS-A Person)
│   │   ├── Room.h / .cpp          # Room class (HAS-A students)
│   │   └── PG.h / .cpp            # PG class (HAS-A owner, HAS-A rooms)
│   │
│   ├── manager/                   # [BUSINESS LOGIC] Controller layer
│   │   ├── PGManager.h / .cpp     # Central database, search, filter, bed tracker
│   │
│   ├── cli/                       # [TERMINAL INTERFACE] Pure C++ CLI
│   │   ├── TerminalApp.h / .cpp   # Interactive menu loop & console UI
│   │   └── cli_main.cpp           # Entry point for StayNear_CLI executable
│   │
│   └── gui/                       # [GRAPHICAL INTERFACE] Qt 6 Desktop GUI
│       ├── AddPGDialog.h / .cpp   # Modal dialog form to register a new PG
│       ├── MainWindow.h / .cpp    # Main desktop window with tables & stats
│       └── gui_main.cpp           # Entry point for StayNear desktop GUI
│
└── standalone/                    # [STANDALONE SINGLE-FILE VERSION]
    └── StayNear_Simple.cpp        # All-in-one file (compiled via single g++ command)
```

---

## 🎓 3. Core OOP Concepts Explained (For Teacher & Viva)

When explaining this project to your teacher, explain these **4 Pillars of OOP + Composition**:

### ① Encapsulation
* **What it is**: Bundling data attributes with methods, and restricting direct external modification.
* **Where in code**: 
  - In [`Person`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/models/Person.h), [`Room`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/models/Room.h), and [`PG`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/models/PG.h), member variables are `private` or `protected`.
  - External access is strictly controlled through public getters (e.g. `getPGName()`, `getRent()`) and setters (e.g. `setOwner()`).

### ② Inheritance (IS-A Relationship)
* **What it is**: Derived classes inheriting common properties and behaviors from a base class.
* **Where in code**:
  - `Person` is the **Base Class** having `name` and `phone`.
  - [`Student`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/models/Student.h) **inherits from** `Person` (`class Student : public Person`). A Student *is a* Person, but also adds `course` and `year`.
  - [`Owner`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/models/Owner.h) **inherits from** `Person` (`class Owner : public Person`). An Owner *is a* Person, but also adds `email`.

### ③ Polymorphism (Method Overriding & Virtual Functions)
* **What it is**: Calling a derived class method through a base class interface at runtime.
* **Where in code**:
  - In `Person.h`: `virtual void display() const;`
  - In `Student.h`: `void display() const override;`
  - In `Owner.h`: `void display() const override;`
  - Also, `Person` defines a `virtual ~Person() = default;` (virtual destructor) to ensure proper memory cleanup when deleting derived objects through base pointers.

### ④ Composition (HAS-A Relationship)
* **What it is**: Constructing complex objects by combining other objects.
* **Where in code**:
  - In `Room.h`: Each `Room` **has a** `std::vector<Student>` representing the students occupying that room.
  - In `PG.h`: Each `PG` **has a** `Owner` instance and **has a** `std::vector<Room>` containing its rooms.

### ⑤ Design Patterns: Singleton Pattern
* **Where in code**:
  - In [`PGManager`](file:///c:/Users/Ravi%20Pandey/Desktop/Project%20Opp/StayNear/src/manager/PGManager.h): `PGManager::instance()` returns a single static instance ensuring consistent data between GUI and CLI.

---

## 🚀 4. How to Build and Run

### Option A: Pure C++ CLI Mode (No Qt required!)
Open PowerShell or Command Prompt:
```bash
# Compile with any C++17 compiler (g++)
g++ -std=c++17 src/models/*.cpp src/manager/*.cpp src/cli/*.cpp -I src/models -I src/manager -I src/cli -o StayNear_CLI.exe

# Run the terminal application
./StayNear_CLI.exe
```

### Option B: Qt 6 Desktop GUI (CMake)
```bash
# Configure and build using CMake
cmake -B build -G "Ninja" -DCMAKE_PREFIX_PATH="C:/Qt/6.11.1/mingw_64"
cmake --build build

# Run the Graphical Desktop App:
./build/StayNear.exe

# Or run CLI mode via the same executable:
./build/StayNear.exe --cli
```

### Option C: Single-File Standalone Version (OnlineGDB / College Lab)
If your college lab does not have CMake installed:
```bash
cd standalone
g++ -std=c++17 StayNear_Simple.cpp -o StayNear_Simple.exe
./StayNear_Simple.exe
```

---

## 💬 5. Frequently Asked Teacher / Viva Questions

| Question | Teacher's Intent | Your Perfect Answer |
| :--- | :--- | :--- |
| **Why did you use `protected` in `Person`?** | Tests understanding of access specifiers. | *"I used `protected` so derived classes like `Student` and `Owner` can directly access `name` and `phone` while still hiding them from external functions."* |
| **Why does `Person` have a `virtual` destructor?** | Tests polymorphism & memory safety. | *"Because when a derived object like `Student` is deleted through a base class `Person*` pointer, a virtual destructor ensures the derived destructor is invoked, preventing memory leaks."* |
| **What is the difference between `Student` and `Room` in relation to `Person`?** | Inheritance vs Composition. | *"`Student` has an **IS-A** relationship with `Person` (Inheritance). `Room` has a **HAS-A** relationship with `Student` (Composition), containing a collection of students living in that room."* |
| **Why did you use `std::vector` instead of raw arrays?** | Modern C++ best practices. | *"`std::vector` dynamically manages its own memory on the heap, preventing buffer overflows and manual `new[]`/`delete[]` memory leaks."* |
| **What is the role of `PGManager`?** | Architecture & Separation of Concerns. | *"`PGManager` separates business logic (searching, filtering, bed calculations) from individual data models (`PG`, `Room`, `Student`), keeping the code clean and modular."* |
