ORI = ft_putnbr_fd.c ft_memmove.c ft_strlen.c ft_strncmp.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_strtrim.c ft_strjoin.c ft_split.c ft_strnstr.c ft_memset.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_bzero.c ft_strlcat.c ft_strlcpy.c ft_substr.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_strdup.c ft_itoa.c ft_strrchr.c ft_toupper.c ft_tolower.c ft_strchr.c ft_isprint.c ft_isascii.c ft_atoi.c ft_strcmp.c ft_strcpy.c
BON = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SRCS_ORI = ${ORI}
SRCS_BON = ${BON}
OBJS_ORI = ${SRCS_ORI:.c=.o}
OBJS_BON = ${SRCS_BON:.c=.o}
OBJ = ${OBJS_ORI} ${OBJS_BON}
ifndef BONUS
	OBJS = ${OBJS_ORI}
else
	OBJS = ${OBJ}
endif
HEAD = ./includes/
NAME = libft.a
AR = ar rc
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c -I ${HEAD} $^ -o $@

${NAME}:	${OBJS}
	${AR} ${NAME} ${OBJS}

clean:
	rm -f ${OBJS_ORI} ${OBJS_BON}

fclean:
	make clean
	rm -f ${NAME}

re:	
	make fclean
	make all
bonus:
	make BONUS=1 all

.PHONY:		all clean fclean re bonus 


#so:
#	#$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
#	cc -nostartfiles -shared -o libft.so $(OBJ)
