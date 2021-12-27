cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(Scacchiera-elettronica)

include_directories(include)

add_library(libs
include/Chessboard.h
src/Chessboard.cpp
include/Piece.h
src/Piece.cpp
src/Rules.cpp
)

add_executable(main
src/Main.cpp
src/Chessboard.cpp
src/Piece.cpp
src/Rules.cpp
)

target_link_libraries(main
libs
)
