NAME = minishell
RLINEFLAGS = -lreadline
CFLAGS = -Wall -Werror -Wextra -I ./includes/

CFILES_UTILS = ft_split.c\
    libft.c\
	libft2.c\
	error.c\
	free.c\

CFILES_EXEC = main.c\
	main_utils.c\
    init.c\
    exec.c\
	exec_utils.c\
	exec_process.c\
	operators_utils.c\
    pipes.c\
	operators.c\
	path.c\
	commands.c\
	signals.c\
	pipe_signal.c\

CFILES_PARSING = env_variables.c\
    parse_line.c\
    ft_itoa.c\
    parse_utils.c\
    checker_parse.c\
	checker_finishparsing.c\
	checker_newlinelen.c\
	checker_parse_utils.c\
	checker_parse_utils2.c\
	checker_operator.c\
	checker_quotes.c\
	checker_pipes.c\
    search_var.c\
	parse_line_args.c\
	parse_line_len.c\
	parse_line_lentonext.c\

CFILES_BUILTINS = cd.c\
	cd_path.c\
	env.c\
	exit.c\
	pwd.c\
	echo.c\
	init_env.c\
	export.c\
	export_utils.c\
	unset.c\
	check_builtins.c\

SRCS_UTILS_DIR = ./src/utils/
SRCS_EXEC_DIR = ./src/exec/
SRCS_PARSING_DIR = ./src/parsing/
SRCS_BUILTINS_DIR = ./src/builtins/

OBJS_DIR = ./.obj/
SRCS_UTILS = $(addprefix $(SRCS_UTILS_DIR), $(CFILES_UTILS))
SRCS_EXEC = $(addprefix $(SRCS_EXEC_DIR), $(CFILES_EXEC))
SRCS_PARSING = $(addprefix $(SRCS_PARSING_DIR), $(CFILES_PARSING))
SRCS_BUILTINS = $(addprefix $(SRCS_BUILTINS_DIR), $(CFILES_BUILTINS))

OBJS_UTILS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_UTILS:.c=.o)))
OBJS_EXEC = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_EXEC:.c=.o)))
OBJS_PARSING = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_PARSING:.c=.o)))
OBJS_BUILTINS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_BUILTINS:.c=.o)))

$(NAME): $(OBJS_UTILS) $(OBJS_EXEC) $(OBJS_PARSING) $(OBJS_BUILTINS) Makefile ./includes/
	$(CC) $(OBJS_UTILS) $(OBJS_EXEC) $(OBJS_PARSING) $(OBJS_BUILTINS) -o $(NAME) $(RLINEFLAGS)

$(OBJS_DIR)%.o: $(SRCS_UTILS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)%.o: $(SRCS_EXEC_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)%.o: $(SRCS_PARSING_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)%.o: $(SRCS_BUILTINS_DIR)%.c
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