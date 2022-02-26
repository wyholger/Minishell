cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)
include_directories(libft)

add_executable(Minishell src/main.c include/minishell.h src/pipe.c src/export_no_arg.c)

target_link_libraries(Minishell ~/Desktop/projects/Minishell/libft/libft.a)
