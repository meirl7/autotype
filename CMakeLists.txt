cmake_minimum_required(VERSION 3.10)
project(AutoType C)

add_executable(autotype main.c)

target_link_libraries(autotype PRIVATE user32)