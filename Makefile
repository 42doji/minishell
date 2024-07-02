NAME=minishell
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS_DIR=srcs
INCLUDES_DIR=includes
OBJS_DIR=bin
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
SRCS=	$(SRCS_DIR)/main.c $(SRCS_DIR)/error_handler.c $(SRCS_DIR)/input_utils.c \
		$(SRCS_DIR)/prompt_utils.c $(SRCS_DIR)/quotes_utils.c $(SRCS_DIR)/tokenizer.c \
		$(SRCS_DIR)/init_utils.c
OBJS=$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
INCLUDES=$(INCLUDES_DIR)/minishell.h
LIBS=-lreadline
RM=rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LIBS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

