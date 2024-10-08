/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:24:17 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/16 00:39:35 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*first_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = ft_strdup("NONE");
	new_token->next = NULL;
	new_token->type = NONE;
	new_token->index = 0;
	return (new_token);
}

void	create_tokens_list(t_token *tokens_list, char *line)
{
	int	table[5];

	table[3] = 1;
	table[4] = 0;
	table[0] = 0;
	while (line[table[0]])
	{
		table[1] = table[0];
		while (line[table[1]] == ' ' || line[table[1]] == '\t')
			table[1]++;
		if (ft_strrchr("|;><", line[table[1]]) != NULL)
			get_space_pipe_semi_redir(tokens_list, line, &table[1], &table[3]);
		if (ft_strrchr("\t <>;|", line[table[1]]) == NULL
			|| line[table[1]] == '\\')
		{
			table[2] = table[1];
			ft_get_word(tokens_list, line, table);
		}
		table[0] = table[1];
	}
	add_token(tokens_list, NEWLINE, ft_strdup("newline"), table[3]);
}

t_token	*ft_lexer(char *line)
{
	t_token	*tokens_list;

	tokens_list = NULL;
	tokens_list = first_token();
	create_tokens_list(tokens_list, line);
	return (tokens_list);
}

void	ft_destoy_token_list(t_token *tokens_list)
{
	t_token	*tmp;

	tmp = NULL;
	while (tokens_list->type != NEWLINE)
	{
		tmp = tokens_list;
		tokens_list = tokens_list->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (tokens_list->type == NEWLINE)
	{
		free(tokens_list->value);
		tokens_list->value = NULL;
		free(tokens_list);
		tokens_list = NULL;
		write(1, CYAN, ft_strlen(CYAN));
	}
}
