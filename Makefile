NAME = minishell



# Name the compiler
CC = gcc
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
MAKE = make -C

FLAGS = -Wall -Wextra -Werror

BLUE = \033[1;34m

SOURCEDIR = ./src
HEADERSDIR = ./headers
OBJECTSDIR = ./objects
READ_FOLDER = readline
LIBFT_HEADER = $(SOURCEDIR)/libft/libft.h
LIBFT_FOLDER = $(SOURCEDIR)/libft

LIBFT_LIB = libft.a

READ_FILES = chars_list_rest.c \
chars_list.c \
get_input.c \
history.c \
line_nodes.c \
readline.c \
terminal_config.c 


all: $(NAME)

libft:
	@$(MAKE) $(LIBFT_FOLDER)

MAIN_FILE = last_arg.c \
main.c \
minishell.c 
	
#OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
#OBJ_LEX = $(addprefix $(OBJECTSDIR)/$(LEX_FOLDER)/, $(LEX_FILES:.c=.o))
# OBJ_EXPA = $(addprefix $(OBJECTSDIR)/$(EXPA_FOLDER)/, $(EXPA_FILES:.c=.o))
#OBJ_PARS = $(addprefix $(OBJECTSDIR)/$(PARS_FOLDER)/, $(PARS_FILES:.c=.o))
OBJ_READ = $(addprefix $(OBJECTSDIR)/$(READ_FOLDER)/, $(READ_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))
OBJS :=  $(OBJ_READ) $(OBJ_MAIN)
LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

$(NAME): libft $(OBJS)
	@$(CC) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@


clean:
	@$(RMDIR) $(OBJECTSDIR)
	@$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
	@$(RM) $(LIBFT_FOLDER)/$(LIBFT_LIB) 
	@$(RM) $(NAME) 

re: fclean $(NAME)

