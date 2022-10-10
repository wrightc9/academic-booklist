cmake_minimum_required(VERSION 3.10)
project(linked_list_a)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_list_a main.cpp book.cpp book.h book_list.cpp book_list.h)
