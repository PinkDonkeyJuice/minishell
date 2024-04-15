NAME = minishell
RLINEFLAGS = -lreadline
CFLAGS = -Werror -Wextra -I ./includes/

CFILES_UTILS = ft_split.c\
    libft.c

CFILES_EXEC = main.c\
    init.c\
    exec.c\
    pipes.c\
    utils_lists.c\

CFILES_PARSING = env_variables.c\
    parse_line.c\
    ft_itoa.c\
    parse_utils.c\
    checker_parse.c\
    search_var.c\

CFILES_BUILTINS = cd.c\
	env.c\
	exit.c\
	pwd.c\
	echo.c\

SRCS_UTILS_DIR = ./src/utils/
SRCS_EXEC_DIR = ./src/exec/
SRCS_PARSING_DIR = ./src/parsing/
SRCS_BUILTINS_DIR = ./src/builtins/

OBJS_DIR = ./.obj/
SRCS_UTILS = $(addprefix $(SRCS_UTILS_DIR), $(CFILES_UTILS))
SRCS_EXEC = $(addprefix $(SRCS_EXEC_DIR), $(CFILES_EXEC))
SRCS_PARSING = $(addprefix $(SRCS_PARSING_DIR), $(CFILES_PARSING))
SRCS_BUILTINS = $(addprefix $(SRCS_BUILTINS_DIR), $(CFILES_BUILTINS))

ALL_SRCS = $(SRCS_UTILS) $(SRCS_EXEC) $(SRCS_PARSING) $(SRCS_BUILTINS)

OBJS = $(ALL_SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(RLINEFLAGS)

$(OBJS_DIR)%.o: $(ALL_SRCS)%.c
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