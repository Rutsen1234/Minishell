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
#endif