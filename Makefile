
NAME = pipex
NAME_bonus = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CRS = Mandatory/pipex.c Mandatory/pipex_utils.c Mandatory/ft_split.c \

BCRS = Bonus/ft_split_bonus.c Bonus/pipex_bonus.c Bonus/pipex_utils_bonus.c \
		Bonus/here_doc.c Bonus/get_next_line.c \

OCRS = $(CRS:.c=.o)
BOCRS = $(BCRS:.c=.o)

all: $(NAME)

bonus: $(NAME_bonus)

clean:
	$(RM) $(CRS:.c=.o) $(BCRS:.c=.o)

fclean: clean
	$(RM) $(NAME) $(NAME_bonus)

re: fclean all Bonus

$(NAME): $(CRS:.c=.o)

$(NAME_bonus): $(BCRS:.c=.o)

$(NAME): $(OCRS)
	$(CC) $(CFLAGS) $(OCRS) -o $(NAME)

$(NAME_bonus): $(BOCRS)
	$(CC) $(CFLAGS) $(BOCRS) -o $(NAME_bonus)
