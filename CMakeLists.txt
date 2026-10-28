cmake_minimum_required(VERSION 4.3.0)
project(interpres VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(interpres main.cpp)

target_sources(interpres 
  PRIVATE
  src/Interpres.cpp
  src/ErrorHandler.cpp
  src/Token.cpp
  src/Scanner.cpp
  src/Expr.cpp
  src/AstPrinter.cpp
  src/Parser.cpp
)
target_include_directories(interpres
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

