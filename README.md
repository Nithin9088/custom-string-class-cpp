# custom-string-class-cpp
# Custom String Class in C++

A custom implementation of a string class in C++ without using `std::string`. This project demonstrates dynamic memory management, operator overloading, constructors, friend functions, and basic string manipulation algorithms.

## Features

### Constructors
- Default constructor
- Parameterized constructor
- Copy constructor

### Operator Overloading
- Assignment (`=`)
- Concatenation (`+`)
- Subscript (`[]`)
- Stream insertion (`<<`)
- Stream extraction (`>>`)
- Comparison operators:
  - `==`
  - `!=`
  - `<`
  - `>`
  - `<=`
  - `>=`

### String Functions
- `strcpy`
- `strncpy`
- `strcmp`
- `strncmp`
- `strcat`
- `strncat`
- `strrev`
- `strupr`
- `strlwr`
- `strchr`
- `strrchr`
- `strstr`
- `strlen`

## Concepts Used

- Object-Oriented Programming
- Dynamic Memory Allocation
- Rule of Three
- Friend Functions
- Operator Overloading
- Pointers
- Character Arrays

## Compilation

```bash
g++ src/main.cpp src/String.cpp -Iinclude -o StringApp
```

Run:

```bash
./StringApp
```

## Example

```cpp
String s1("Hello");
String s2(" World");

String s3 = s1 + s2;

cout << s3;
```

## Author

Your Name
