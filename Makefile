
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CRS = Mandatory/pipex.c pipex_utils.c ft_split.c \

OCRS = $(CRS:.c=.o)

all: $(NAME)

clean:
	$(RM) $(CRS:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(CRS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@
