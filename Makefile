NAME = minishell

# Source files
SRCS = $(addprefix src/, \
	print_cat.c handle-c.c \
	$(addprefix builtin/, \
		cd.c \
		echo.c \
		env.c \
		exit.c \
		export.c \
		pwd.c \
		unset.c \
	) \
	$(addprefix exec/, \
		exec.c \
		handle_builtins.c \
		handle_redir.c \
		fork_exec.c \
		handle_hdoc.c \
		name_file.c \
		redir.c \
		check_files.c \
	) \
	$(addprefix parsing/, \
		$(addprefix lexer/, \
			lexer.c \
		) \
		$(addprefix expand/, \
			expand.c \
		) \
		$(addprefix syntax/, \
			syntax_checks.c \
		) \
		cmd_finder.c \
		env_parse.c \
		files_validator.c \
		ft_split_args_utils.c \
		ft_split_args.c \
		lexer_to_cmd.c \
		main_parser.c \
	) \
	$(addprefix utils/, \
		error.c \
		exit_free.c \
		utils.c \
		name_file.c \
		pid_utils.c \
		env_utils.c \
		list.c \
		remove_double_points.c \
		change_dir.c \
		fds.c \
		ascii_to.c \
	) \
	minishell.c \
	)

# Object files directory and object files
OBJ_DIR = .obj
OBJ = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -g3

# Libraries
LIB = -Llibft -lft -lreadline
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Clean up command
RM = rm -rf

# Directory structure
DIRS = $(OBJ_DIR) \
	$(OBJ_DIR)/parsing \
	$(OBJ_DIR)/parsing/lexer \
	$(OBJ_DIR)/parsing/expand \
	$(OBJ_DIR)/parsing/syntax \
	$(OBJ_DIR)/builtin \
	$(OBJ_DIR)/exec \
	$(OBJ_DIR)/utils

# Header files
HEADERS = $(addprefix includes/, \
		builtins.h \
		exec.h \
		minishell.h \
		parsing.h \
		struct.h \
		utils.h \
		)
LIBFT_HEADERS = $(addprefix libft/, \
		ft_printf.h \
		get_next_line.h \
		libft.h \
		)

# Targets
all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFT_HEADERS) libft/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c $(HEADERS) Makefile $(LIBFT) | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re