/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:35:59 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/13 11:45:19 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

void	ft_check_digit(char *arg)
{
	char	*error;
	int		estatus;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if (g_vars.history)
				g_vars.history = ft_destroy_history(g_vars.history);
			error = ft_strjoin(arg, ": numeric argument required");
			estatus = ft_put_err("exit: ", error, 255);
			free(error);
			exit(estatus);
		}
		i++;
	}
}

int	ft_exit(t_args *args)
{
	int		exit_code;
	char	*arg_value;
	int		i;

	i = 0;
	exit_code = 0;
	if (g_vars.infork == NO)
		ft_putendl_fd("exit", 1);
	if (args != NULL && args->value != NULL)
	{
		arg_value = args->value;
		while (arg_value[i])
		{
			if (!ft_isdigit(arg_value[i]) && arg_value[i] != '-'
				&& arg_value[i] != '+')
				return (ft_put_err("exit", ": numeric argument required", 2));
			i++;
		}
		exit_code = ft_atoi(arg_value);
		if (args->next != NULL)
			return (ft_put_err("exit", ": too many arguments", 1));
	}
	if (g_vars.history)
		g_vars.history = ft_destroy_history(g_vars.history);
	exit(exit_code);
}

int	ft_unset(t_args *args, t_env **head)
{
	int	ret;

	ret = 0;
	while (args != NULL)
	{
		if (args->value == NULL)
			ret = ft_put_err("`'", ": not a valid identifier", 1);
		else
			ft_delete_from_list(head, args->value);
		args = args->next;
	}
	return (ret);
}
