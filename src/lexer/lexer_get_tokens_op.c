/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 09:35:18 by zjamali           #+#    #+#             */
/*   Updated: 2024/08/15 21:41:02 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// static void	get_redir(t_token *tokens_list, char *line, int *j, int *index)
// {
// 	if (line[*j] == '>')
// 	{
// 		if (line[*j + 1] == '>')
// 		{
// 			add_token(tokens_list, DOUBLE_GREAT, ft_strdup(">>"), *index, NULL);
// 			*j = *j + 2;
// 			(*index)++;
// 		}
// 		else
// 		{
// 			add_token(tokens_list, GREAT, ft_strdup(">"), *index, NULL);
// 			(*j)++;
// 			(*index)++;
// 		}
// 	}
// 	else if (line[*j] == '<')
// 	{
// 		if (line[*j + 1] == '<')
// 		{
// 			add_token(tokens_list, HEREDOC, ft_strdup("<<"), *index, line);
// 			*j = (*j) + 2;
// 			(*index)++;
// 		}
// 		if (line[*j] == '<')
// 		{
// 			add_token(tokens_list, LESS, ft_strdup("<"), *index, NULL);
// 			(*j)++;
// 			(*index)++;
// 		}
// 	}
// }

static void	handle_less_redirection(t_token *tokens_list, char *line,
	int *j, int *index)
{
	if (line[*j + 1] == '<')
	{
		add_token(tokens_list, HEREDOC, ft_strdup("<<"), *index, line);
		*j += 2;
	}
	else
	{
		add_token(tokens_list, LESS, ft_strdup("<"), *index, NULL);
		(*j)++;
	}
	(*index)++;
}

static void	get_redir(t_token *tokens_list, char *line, int *j, int *index)
{
	if (line[*j] == '>')
	{
		if (line[*j + 1] == '>')
		{
			add_token(tokens_list, DOUBLE_GREAT, ft_strdup(">>"), *index, NULL);
			*j = *j + 2;
			(*index)++;
		}
		else
		{
			add_token(tokens_list, GREAT, ft_strdup(">"), *index, NULL);
			(*j)++;
			(*index)++;
		}
	}
	else if (line[*j] == '<')
	{
		handle_less_redirection(tokens_list, line, j, index);
	}
}

void	get_space_pipe_semi_redir(t_token *tokens_list,
		char *line, int *j, int *index)
{
	char	*token;

	if (line[*j] == '|')
	{
		if (line[*j + 1] == '|')
			token = ft_strdup("||");
		else
			token = ft_strdup("|");
		add_token(tokens_list, PIPE, token, *index, NULL);
		(*index)++;
		(*j)++;
	}
	else if (line[*j] == ';')
	{
		if (line[*j + 1] == ';')
			token = ft_strdup(";;");
		else
			token = ft_strdup(";");
		add_token(tokens_list, SEMI, token, *index, NULL);
		(*index)++;
		(*j)++;
	}
	else
		get_redir(tokens_list, line, j, index);
}
