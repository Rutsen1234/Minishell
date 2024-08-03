
#include "../../headers/execution.h"

void	ft_loop(t_args *args)
{
	while (args != NULL)
	{
		if (args->value != NULL)
			ft_putstr_fd(args->value, 1);
		if (args->next != NULL)
			ft_putchar_fd(' ', 1);
		args = args->next;
	}
}

int	ft_isitn(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] == 'n' && arg[i])
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

int ft_echo(t_args *args) 
{
    int new_line = 1;

    if (args && ft_isitn(args->value)) {
        new_line = 0;
        args = args->next;
    }

    if (args == NULL) {
        ft_putchar_fd('\n', 1);
    } else {
        ft_loop(args);
        if (new_line) {
            ft_putchar_fd('\n', 1);
        }
    }

    return 0;
}
int	ft_pwd(t_env **head)
{
	char	*pwd = getcwd(NULL, 100);

	if (pwd)
		ft_putendl_fd(pwd, 1);
	else
	{
		t_env *temp = ft_search_in_list(head, "PWD");
		if (temp)
			ft_putendl_fd(temp->value, 1);
	}
	free(pwd);
	return (0);
}

int	ft_env(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->value != NULL)
		{
			ft_putstr_fd(temp->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(temp->value, 1);
		}
		temp = temp->next;
	}
	return(0);
}