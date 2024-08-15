/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:02:53 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/15 22:14:08 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"
#include "../../headers/minishell.h"


int	ft_count_list(t_env **head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = *head;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void	ft_free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

char	**ft_args_to_arr(t_simple_cmd *cmd)
{
	t_args	*arg_node;
	int		num_args;
	char	**args;
	int		i;

	arg_node = cmd->args;
	num_args = ft_count_args(&arg_node) + 1;
	args = malloc((num_args + 1) * sizeof(char *));
	args[0] = ft_strdup(cmd->command);
	i = 1;
	while (arg_node)
	{
		if (arg_node->value == NULL && arg_node->inside_quotes == 2)
			arg_node->value = ft_strdup("");
		args[i] = ft_strdup(arg_node->value);
		i++;
		arg_node = arg_node->next;
	}
	args[i] = NULL;
	return (args);
}

void	ft_init_env(t_env **head, char **env)
{
	int		i;
	char	**var;
	t_env	*new_node;

	i = 0;
	while (env[i])
	{
		var = splitforenv(env[i]);
		new_node = ft_create_node(var[0], var[1]);
		if (*head)
			ft_add_to_list(head, new_node);
		else
			*head = new_node;
		free(var[0]);
		free(var[1]);
		free(var);
		i++;
	}
}

int	ft_redirection(t_mini *mini, t_redirection *redirect)
{
	while (redirect != NULL)
	{
		if (redirect->type == RE_GREAT && ft_great_than(&mini->red_fd[1],
				redirect))
			return (1);
		if (redirect->type == RE_LESS && ft_less_than(&mini->red_fd[0],
				redirect))
			return (1);
		if (redirect->type == RE_DOUBLE_GREAT
			&& ft_double_great(&mini->red_fd[1], redirect))
			return (1);
		// if (redirect->type == RE_HEREDOC && ft_heredoc(&mini->red_fd[0],
		// 		redirect))
		// 	return (1);
		redirect = redirect->next;
	}
	return (0);
}
