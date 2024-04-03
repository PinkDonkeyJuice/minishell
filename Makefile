NAME = minishell
RLINEFLAGS = -lreadline
CFLAGS = -Wall -Werror -Wextra -I ./includes/
CFILES = utils/ft_split.c\
	utils/libft.c\
	exec/main.c\
	exec/init.c\
	exec/exec.c\
	exec/pipes.c\
	exec/utils_lists.c\
	env/env_variables.c\
	# parsing/handle_operators.c\
	# parsing/parse_line.c\
	# utils/GNL/get_next_line\
	# utils/GNL/get_next_line_utils.c

SRCS_DIR = ./src/
OBJS_DIR = ./.obj/

SRCS = $(addprefix $(SRCS_DIR), $(CFILES))

OBJS = $(addprefix $(OBJS_DIR), $(CFILES:.c=.o))

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(RLINEFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)env
	mkdir -p $(OBJS_DIR)exec
	mkdir -p $(OBJS_DIR)parsing
	mkdir -p $(OBJS_DIR)utils
	mkdir -p $(OBJS_DIR)utils/GNL
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re