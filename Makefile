NAME = minishell
RLINEFLAGS = -lreadline
CFLAGS = -Wall -Werror -Wextra -I ./includes/
CFILES = ft_split.c\
	libft.c\
	main.c\
	init.c\

SRCS_DIR = ./src/
OBJS_DIR = ./.obj/

SRCS = $(addprefix $(SRCS_DIR), $(CFILES))

OBJS = $(addprefix $(OBJS_DIR), $(CFILES:.c=.o))

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(RLINEFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re