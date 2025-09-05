# KFD Test Assignment: Library Management System

## Task Description

Library management system created.

To run, go to "src\cmake-build-debug" and run "LibraryManagementSystem.exe" (works for Windows Mingw, not tested for other environments)

### What was built:
A working console application that manages:
- **Books** (add, remove, search)
- **Users** (different types: Student, Faculty, Guest) 
- **Borrowing operations** (borrow, return, track overdue)


### ✅ **It works**
- Program runs without crashes
- Basic features work (add book, borrow, return)
- Menu navigation functions

### ✅ **OOP Understanding**
- Different user types with different behavior
- Proper inheritance (User → Student/Faculty/Guest)
- Basic encapsulation (private fields, public methods)

### ✅ **Data Structure Choices**
- HashMap/Map for books and users (fast lookup)
- Set for unique collections where appropriate
- Can explain your choices

### ✅ **Basic Programming Skills**
- Handles invalid input gracefully
- Code is (mostly) readable and organized
- Reasonable variable/method names

## Required Features
1. Add/remove books
2. Register users (different types)
3. Borrow/return books with validation
4. Search books by title/author/ISBN
5. View overdue books

## Deliverables
1. **Working code** that demonstrates the features
2. **README** with setup instructions

## Example terminal Commands
```
unknown_command
bor
ad coolBook pal 712938
ad redBook gleb 1283091
ad greenBook somebody 21312
reg me hoop@gmail.com
add wrong dev 1831203
reg him pppppppp@tandex.ru student
add wrong1 dev 1231111
add wrong2 dev 1312412313
add wrong3 dev 123151555
bor 1 1312412313
rem 1312412313
ret 1312412313
rem 1312412313
sear omi
bor 2 1831203
bor 2 1312412313
bor 2 123151555
bor 2 21312
bor 2 1283091
history
his 5

```

## Evaluation Notes

### Good Signs
- Program works for basic scenarios
- Clear inheritance structure  
- Appropriate HashMap/List usage
- Some error handling
- Readable code organization

### Red Flags
- Doesn't compile/run
- No inheritance used
- Only arrays, no collections
- No error handling
- Unreadable code, no linting

**Goal**: Find students who understand basics and can think through problems systematically. Perfect code not required - working code with reasonable design is what we want to see.
