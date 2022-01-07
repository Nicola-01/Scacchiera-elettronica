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

add_executable(scacchiera
src/Scacchiera.cpp
src/Chessboard.cpp
src/Piece.cpp
src/Rules.cpp
src/Has_valid_move.cpp
)

add_executable(replay
src/Replay.cpp
src/Chessboard.cpp
src/Piece.cpp
src/Rules.cpp
)

target_link_libraries(scacchiera
libs 
)

target_link_libraries(replay
libs 
)
