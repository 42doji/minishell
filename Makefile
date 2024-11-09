# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 10:28:04 by doji              #+#    #+#              #
#    Updated: 2024/11/08 19:47:09 by junmin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

NAME = minishell
LIBFT = ./libft/libft.a
INCLUDES = includes
LIBS = -ltermcap -lncurses -lreadline

SRC = 	./srcs/shell/command.c \
		./srcs/shell/command_cd.c \
		./srcs/shell/command_echo.c \
		./srcs/shell/command_env.c \
		./srcs/shell/command_exit.c \
		./srcs/shell/command_export.c \
		./srcs/shell/command_pwd.c \
		./srcs/shell/command_unset.c \
		./srcs/shell/command_util1.c \
		./srcs/shell/command_util2.c \
		./srcs/shell/execution.c \
		./srcs/shell/execve.c \
		./srcs/shell/redirect.c \
		./srcs/shell/here_doc.c \
		./srcs/shell/here_doc2.c \
		./srcs/shell/pipe.c \
		./srcs/shell/init_minishell.c \
		./srcs/util/free1.c \
		./srcs/util/free2.c \
		./srcs/util/signal.c \
		./srcs/util/util1.c \
		./srcs/util/util2.c \
		./srcs/util/util3.c \
		./srcs/util/print_error.c \
		./srcs/parser/token_check.c \
		./srcs/parser/init.c \
		./srcs/parser/check_quote.c \
		./srcs/parser/syntax_error.c \
		./srcs/parser/parser.c \
		./srcs/parser/parser_util.c \
		./srcs/parser/parser_util2.c \
		./srcs/parser/lexer.c \
		./srcs/parser/env.c \
		./srcs/parser/tokenizer.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -s -C ./libft

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) main.c $(LIBFT) -o $(NAME) -I $(INCLUDES) $(LIBS)
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	@make -s clean -C ./libft
	@$(RM) $(OBJ)

fclean: clean
	@make -s fclean -C ./libft
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re 
