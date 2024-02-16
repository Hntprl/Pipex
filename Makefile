
NAME = pipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ar rcs
RM = rm -f

SRC	= pipex.c pipex_utils.c ft_split.c \

SRC_OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(LIB) $(NAME) $(SRC_OBJ) $(NAME)

clean:
	$(RM) $(SRC_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT:
