# Interpres

Interpres is a C++ interpreter project focused on learning the fundamentals of programming language implementation, including lexical analysis, parsing, abstract syntax trees, and expression evaluation.

The project aims to build an interpreter with a clear architecture, modern C++ practices, and a modular design.

## Project Structure

The repository separates public headers from source implementations.

```text
include/
  AstPrinter.hpp
  ErrorHandler.hpp
  Expr.hpp
  Interpres.hpp
  Parser.hpp
  Scanner.hpp
  Token.hpp
  TokenType.hpp

src/
  AstPrinter.cpp    
  ErrorHandler.cpp
  Expr.cpp
  Interpres.cpp
  Parser.cpp
  Scanner.cpp
  Token.cpp

main.cpp
CMakeLists.txt
```
## Tech Stack

- C++
- CMake

## Building

### Requirements

- A C++ compiler with C++23
- CMake

### Compile

Configure the project:

```bash
cmake -B build
```

Build the executable:

```bash
cmake --build build
```

Run the interpreter:

```bash
./build/interpres
```

## Project Goals

- Understand the fundamentals of interpreter design
- Implement lexical analysis and parsing
- Represent expressions using abstract syntax trees
- Apply object-oriented programming and modern C++ features
- Maintain a modular and extensible architecture
- Explore runtime evaluation and error handling

## References

- Crafting Interpreters — Robert Nystrom

## License

MIT
