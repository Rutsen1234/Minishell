/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 09:28:52 by zjamali           #+#    #+#             */
/*   Updated: 2024/08/13 11:10:31 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_the_beginning_of_word(int c)
{
	if (c == 92)
		return (1);
	else if (c == 39)
		return (2);
	else if (c == 34)
		return (3);
	else
		return (0);
}

static void	add_token_and_increament_index(t_token *tokens_list, char *word,
			int *table, int j)
{
	add_token(tokens_list, WORD, word, table[3],NULL);
	table[1] = j;
	table[3]++;
}

void ft_get_word(t_token *tokens_list, char *line, int *table)
{
    int quoting;
    char *word = NULL;
    int j = table[1];

    while (line[j])
    {
        quoting = check_the_beginning_of_word(line[j]);
        if (quoting == 0)
        {
            if (line[j] == '<' && line[j + 1] == '<')
            {
                // Add heredoc token and skip the rest of the line
                // add_token(tokens_list, HEREDOC, "<<", table[3], line);
                table[1] = j + 2;  // Move past the "<<"
                return;  // Stop further processing for this token
            }
            word = ft_get_words(line, &j, word, &quoting);
            if (ft_strchr("\t ><|;", line[j]))
                break;
        }
        else if (quoting > 0)
        {
            word = ft_get_words(line, &j, word, &quoting);
            if (line[j] == ' ' || line[j] == '\t')
                break;
        }
    }
    add_token_and_increament_index(tokens_list, word, table, j);
}

