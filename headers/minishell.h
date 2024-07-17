#ifndef MINISHELL_H
# define MINISHELL_H


# define GREEN "\e[1;32m"
# define RESET "\e[0m"


/***** ENV LIST ******/

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

/****PIPELINE LISTS */
typedef struct s_pipe_line
{
	int					simple_cmd_count;
	struct s_pipe_line	*next;
	t_simple_cmd		*child;
}				t_pipe_line;

typedef struct s_cursor{
	int	line_postion;
	int	col_position;
}				t_cursor;

/*********COMMAND-LINE-NODE */
typedef struct s_char_list{
	char				value;
	int					len;
	struct s_char_list	*next;
}				t_char_list;

typedef struct s_lines_list{
	char				value;
	int					history;
	int					index;
	bool				up_or_down;
	t_char_list			*char_list;
	t_char_list			*origin_char_list;
	struct s_lines_list	*next;
	struct s_lines_list	*prev;
}				t_lines_list;

typedef struct s_readline
{
	char		*term_type;
	int			term_fd;
	int			line_count;
	int			colums_count;
	long		c;
	char		*path;
	char		*line;
	t_cursor	cursor;
}t_readline;




#endif