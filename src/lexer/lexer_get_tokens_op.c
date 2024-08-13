/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 09:35:18 by zjamali           #+#    #+#             */
/*   Updated: 2024/08/10 14:36:52 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	get_redir(t_token *tokens_list, char *line, int *j, int *index)
{
	if (line[*j] == '>')
	{
		if (line[*j + 1] == '>')
		{
			add_token(tokens_list, DOUBLE_GREAT, ft_strdup(">>"), *index);
			*j = *j + 2;
			(*index)++;
		}
		else
		{
			add_token(tokens_list, GREAT, ft_strdup(">"), *index);
			(*j)++;
			(*index)++;
		}
	}
<<<<<<< HEAD
	// else if (line[*j] == '<')
	// {
		if (line[*j + 1] == '<')
		{
			add_token(tokens_list, HEREDOC, ft_strdup("<<"), *index);
			*j = *j + 2;
			(*index)++;
		}
		// else
		// {
		// 	add_token(tokens_list, LESS, ft_strdup("<"), *index);
		// 	(*j)++;
		// 	(*index)++;
		// }
	}
// }
=======
	else if (line[*j] == '<')
	{
		if (line[*j + 1] == '<')
		{
			printf("check\n");
			add_token(tokens_list, HEREDOC, ft_strdup("<<"), *index);
			*j = (*j)+ 2;
			(*index)++;
		}
		else if (line[*j] == '<')
		{
			printf("checkff\n");
			add_token(tokens_list ,LESS, ft_strdup("<"), *index);
			(*j)++;
			(*index)++;
		}		
	}
	
}
>>>>>>> 43963aa (dujfoisd)

void	get_space_pipe_semi_redir(t_token *tokens_list,
							   char *line, int *j, int *index)
{
	char	*token;

	if(line[*j+ 1] == '<')
	{
		printf("E");
	}
	if (line[*j] == '|')
	{
		if (line[*j + 1] == '|')
			token = ft_strdup("||");
		else
			token = ft_strdup("|");
		add_token(tokens_list, PIPE, token, *index);
		(*index)++;
		(*j)++;
	}
	else if (line[*j] == ';')
	{
		if (line[*j + 1] == ';')
			token = ft_strdup(";;");
		else
			token = ft_strdup(";");
		add_token(tokens_list, SEMI, token, *index);
		(*index)++;
		(*j)++;
	}
	else
		get_redir(tokens_list, line, j, index);
}
