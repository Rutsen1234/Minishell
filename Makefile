# Name of the final executable
NAME = minishell

# Project's directories
SOURCEDIR := ./src
HEADERSDIR := ./headers
OBJECTSDIR := ./objects
EXEC_FOLDER = execution
LEX_FOLDER = lexer
PARS_FOLDER = parse
EXPA_FOLDER = expansion
READ_FOLDER = readline
LIBFT_HEADER = $(SOURCEDIR)/libft/libft.h
LIBFT_FOLDER = $(SOURCEDIR)/libft


# Name of variables
LIBFT_LIB = libft.a
LIBS = -lncurses
FLAGS = -Wall -Wextra -Werror -g3
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


# Execution files variable
EXEC_FILES =  ft_cd.c \
ft_check_path.c \
ft_echo_pwd_env.c \
ft_execution.c \
ft_exit.c \
ft_export.c \
ft_init_env.c \
l1.c \
lo.c \
ft_pipes.c \
ft_redirection.c \
ft_utlis.c 

# Lexer files variable

LEX_FILES = lexer_get_tokens_op.c \
lexer_get_tokens_word.c \
lexer_get_tokens.c \
lexer.c lexer_continue.c \
addtokenforheredoc.c

# Parse files variable

PARS_FILES = check_syntax.c \
check_token_continue.c \
check_tokens.c \
check_word.c \
create_ast.c \
create_nodes.c \
destoy_nodes.c \
parser.c

# Readline files variable
READ_FILES = chars_list_rest.c \
chars_list.c \
get_input.c \
history.c \
line_nodes.c \
readline.c \
terminal_config.c 

# Expansion files variable
EXPA_FILES = expand_args.c \
expand_command.c \
expand_dble_qoutes_word.c \
expand_non_qoutes_word.c \
expand_redirction.c \
expand_special_params_in_quotes.c \
expand_special_params.c \
expand_word.c \
expansion.c \
utils_continue.c \
utils.c

# Main file variable

MAIN_FILE = last_arg.c \
main.c \
minishell.c 

# Define objects for all sources
OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
OBJ_LEX = $(addprefix $(OBJECTSDIR)/$(LEX_FOLDER)/, $(LEX_FILES:.c=.o))
OBJ_EXPA = $(addprefix $(OBJECTSDIR)/$(EXPA_FOLDER)/, $(EXPA_FILES:.c=.o))
OBJ_PARS = $(addprefix $(OBJECTSDIR)/$(PARS_FOLDER)/, $(PARS_FILES:.c=.o))
OBJ_READ = $(addprefix $(OBJECTSDIR)/$(READ_FOLDER)/, $(READ_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))
OBJS := $(OBJ_EXEC) $(OBJ_LEX) $(OBJ_EXPA) $(OBJ_PARS) $(OBJ_READ) $(OBJ_MAIN)
LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

# Name the compiler
CC = gcc -fsanitize=address -g3

# OS specific part
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null


.PHONY: all fclean 

all: credit $(NAME)
	
libft:
	echo "$(BLUE)█████████████████████████ Making LIBFT █████████████████████████$(RESET)"
	$(MAKE) $(LIBFT_FOLDER)
	echo "$(BLUE)███████████████████████ Making minishell ███████████████████████$(RESET)"

$(NAME): libft $(OBJS)
	$(CC) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@
	echo "$(BLUE)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"

$(OBJECTSDIR)/%.o : $(SOURCEDIR)/%.c $(HEADERSDIR)/*.h
	$(MKDIR) $(dir $@)
	echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	$(CC) $(FLAGS) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build

clean:
	echo "$(RED)deleting$(RESET): " $(OBJECTSDIR)
	$(RMDIR) $(OBJECTSDIR) $(ERRIGNORE)
	echo "$(RED)deleting$(RESET): " "libft objects"
	$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
	echo "$(RED)deleting$(RESET): " $(LIBFT_FOLDER)/$(LIBFT_LIB)
	$(RM) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(ERRIGNORE)
	echo "$(RED)deleting$(RESET): " $(NAME)
	$(RM) $(NAME) $(ERRIGNORE)

re: fclean $(NAME)

credit:
	echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	echo "         Made with love by
