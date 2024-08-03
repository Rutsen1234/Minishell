

#include "../../headers/execution.h"

void	ft_destroy_env_list(t_env *head)
{
	t_env	*temp;
	t_env	*change;

	temp = head;
	if (head == NULL)
		return ;
	while (temp != NULL)
	{
		free(temp->name);
		free(temp->value);
		change = temp->next;
		free(temp);
		temp = change;
	}
}

int	ft_count_args(t_args **args)
{
	int		i;
	t_args	*temp;

	i = 0;
	temp = *args;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void ft_do_backups(int flag) 
{
    static int std_fds[3];

    if (flag == 1) {
        std_fds[0] = dup(STDIN_FILENO);
        std_fds[1] = dup(STDOUT_FILENO);
        std_fds[2] = dup(STDERR_FILENO);
    } else {
        dup2(std_fds[0], STDIN_FILENO);
        dup2(std_fds[1], STDOUT_FILENO);
        dup2(std_fds[2], STDERR_FILENO);
    }
}

int	ft_put_err(char *input, char *message, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (input != NULL)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (ret);
}

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
