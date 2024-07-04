cmake_minimum_required(VERSION 3.22.1)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_executable(minishell
        srcs/tokenizer.c
        srcs/error_handler.c
        srcs/prompt_utils.c
        srcs/main.c
        srcs/quotes_utils.c
        srcs/envp_utils.c
        srcs/builtin_echo.c
        srcs/signal_handler.c)
