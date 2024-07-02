cmake_minimum_required(VERSION 3.28)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_executable(minishell
        srcs/tokenizer.c
        srcs/error_handler.c)
