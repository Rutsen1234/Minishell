/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:40:08 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/13 12:02:25 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

int	ft_checkargs(t_args **args)
{
	t_args	*temp;
	int		ret;
	char	*error;
	char	*full_error;

	temp = *args;
	ret = 0;
	while (temp != NULL)
	{
		if (temp->value == NULL)
			ret = ft_put_err("export:", " `': not a valid identifier", 1);
		else if (!(ft_isalpha(temp->value[0]) || temp->value[0] == '_'))
		{
			error = ft_strjoin(" `", temp->value);
			full_error = ft_strjoin(error, "': not a valid identifier");
			free(error);
			ret = ft_put_err("export:", full_error, 1);
			free(full_error);
		}
		temp = temp->next;
	}
	return (ret);
}

int	ft_print_export(t_env **head)
{
	t_env	*sorted_list;
	t_env	*current;

	sorted_list = ft_sort_list(head);
	current = sorted_list;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->name, 1);
		if (current->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
	ft_destroy_env_list(sorted_list);
	return (0);
}

void	ft_add_or_replace(t_env **head, char **split, int join)
{
	t_env	*node;
	char	*new_value;
	t_env	*new_node;

	node = ft_search_in_list(head, split[0]);
	if (node != NULL)
	{
		if (join == YES)
		{
			new_value = ft_strjoin(node->value, split[1]);
			free(split[1]);
			split[1] = new_value;
		}
		if (split[1] != NULL)
		{
			ft_replaceit(head, split[0], split[1]);
		}
	}
	else
	{
		new_node = ft_create_node(split[0], split[1]);
		ft_add_to_list(head, new_node);
	}
}

void	ft_add_var(t_env **head, t_args *args)
{
	char	**split;
	int		join;

	while (args != NULL)
	{
		split = splitforenv(args->value);
		join = (split[0][ft_strlen(split[0]) - 1] == '+');
		if (join)
		{
			split[0][ft_strlen(split[0]) - 1] = '\0';
		}
		ft_add_or_replace(head, split, join);
		free(split[0]);
		free(split[1]);
		free(split);
		args = args->next;
	}
}

int	ft_export(t_env **head, t_args *args)
{
	int	ret;

	ret = 0;
	if (args == NULL)
	{
		return (ft_print_export(head));
	}
	ret = ft_checkargs(&args);
	ft_add_var(head, args);
	return (ret);
}
