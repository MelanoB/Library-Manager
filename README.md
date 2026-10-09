# Library Manager

A console-based library management system written in modern C++ (C++17).
It manages four kinds of library items, tracks borrowing and returns, calculates
late fees, and saves/loads its data from a text file.

Built as a university assignment to practice object-oriented design,
polymorphism, and defensive input handling.

## Features

- **Four item types:** Book, Magazine, DVD, Research Paper
- **Add / delete / display** items, with unique-ID checking
- **Search** by title, creator, type, ID, or year (case-insensitive)
- **Borrow and return** items, with a per-type late fee calculated on return
- **Sort** by title, year, type, or availability
- **Report:** totals, available vs. borrowed, count per type, oldest and newest item
- **Save / load** to a pipe-delimited text file (`library_data.txt`)
- **Input validation:** bad input (letters instead of numbers, empty fields,
  invalid years, duplicate IDs) shows an error message instead of crashing

## Late fees

| Item type      | Fee per overdue day (GEL) |
|----------------|---------------------------|
| Book           | 0.50                      |
| Magazine       | 0.30                      |
| DVD            | 1.00                      |
| Research Paper | 0.20                      |

## OOP design

```
LibraryItem  (abstract base class)
├── Book
├── Magazine
├── DVD
└── ResearchPaper
```

- `LibraryItem` declares pure virtual methods: `display()`, `getType()`,
  `saveToFile()`, and `calculateLateFee()`. Each subclass overrides them.
- `LibraryManager` owns every item through `std::vector<std::unique_ptr<LibraryItem>>`,
  so memory is managed automatically (no raw `new`/`delete`).
- Sorting and reporting use STL algorithms (`std::sort`, `std::min_element`,
  `std::max_element`) with lambdas.
- Errors are reported with `std::runtime_error` and handled in `main()`.

## Project structure

```
Library-Manager/
├── CMakeLists.txt
├── data/library_data.txt     # sample data (9 items)
└── src/
    ├── Driver.cpp            # menu loop and top-level error handling
    ├── LibraryManager.h/.cpp # collection management, file I/O, reports
    ├── LibraryItem.h/.cpp    # abstract base class
    └── Book / Magazine / DVD / ResearchPaper (.h/.cpp)
```

## Build and run

Requires a C++17 compiler and CMake 3.10+.

```bash
git clone https://github.com/MelanoB/Library-Manager.git
cd Library-Manager
cmake -S . -B build
cmake --build build
./build/library_manager        # on Windows: build\Debug\library_manager.exe
```

The build copies the sample data next to the executable, so choose
**13. Load From File** in the menu to try it with data right away.
Run the program from the folder that contains the executable and
`library_data.txt` (the file is looked up in the current directory).

**Visual Studio:** use *File → Open → Folder* and select the project folder;
VS detects `CMakeLists.txt` automatically.

## Example session

```
========== LIBRARY MENU ==========
...
Enter choice: 13
File loaded successfully

Enter choice: 11

===== LIBRARY REPORT =====
Total Items: 9
Available Items: 8
Borrowed Items: 1
...
```

## Data file format

One item per line, fields separated by `|`. The sixth field is `1` if the item is
available and `0` if borrowed:

```
Book|101|Introduction to C++ Programming|John Smith|2021|1|450|Programming
DVD|301|The Imitation Game|Morten Tyldum|2014|0|114|PG-13
```

## Known limitations / ideas for future work

- Titles or names containing the `|` character would corrupt the data file
  (an escape mechanism or a different format such as JSON/CSV would fix this).
- Borrowing does not track *who* borrowed an item or when it is due; overdue
  days are entered manually when returning.
- No automated tests yet (a good next step: unit tests for `calculateLateFee`
  and the file load/save round-trip).
- Sorting by title is case-sensitive.
