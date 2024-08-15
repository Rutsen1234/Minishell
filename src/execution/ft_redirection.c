/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:05 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/15 21:21:26 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"
#include "../../headers/minishell.h"

int	ft_open_and_redirect(int *fd, char *file_name, int flags, int std_fd)
{
	*fd = open(file_name, flags, 0644);
	if (*fd < 0)
		return (ft_file_err(file_name));
	dup2(*fd, std_fd);
	close(*fd);
	return (0);
}

int	ft_great_than(int *fd, t_redirection *redirect)
{
	return (ft_open_and_redirect(fd, redirect->file_name,
			O_CREAT | O_TRUNC | O_WRONLY, STDOUT_FILENO));
}

int	ft_less_than(int *fd, t_redirection *redirect)
{
	return (ft_open_and_redirect(fd, redirect->file_name, O_RDONLY,
			STDIN_FILENO));
}

int	ft_double_great(int *fd, t_redirection *redirect)
{
	return (ft_open_and_redirect(fd, redirect->file_name,
			O_CREAT | O_APPEND | O_WRONLY, STDOUT_FILENO));
}

int ft_heredoc(int *fd, t_redirection *redirect)
{
	char	*line;
	size_t	len;
	size_t	delimiter_len;

	char *delimiter = redirect->file_name;
	line = NULL;
	len = 0;
	printf("hihi\n");
	*fd = open("heredoc_tmp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd < 0)
	{
		perror("Error opening heredoc_tmp.txt for writing");
		return (-1);
	}
	while (1)
	{
		printf("> ");
		if (getline(&line, &len, stdin) == -1)
		{
			perror("Error reading line");
			break ;
		}
		delimiter_len = strlen(delimiter);
		if (strncmp(line, delimiter, delimiter_len) == 0
			&& (line[delimiter_len] == '\n' || line[delimiter_len] == '\0'))
			break ;
		if (write(*fd, line, strlen(line)) == -1)
		{
			perror("Error writing to heredoc_tmp.txt");
			free(line);
			close(*fd);
			return (-1);
		}
	}
	free(line);
	close(*fd);
	*fd = open("heredoc_tmp.txt", O_RDONLY);
	if (*fd < 0)
	{
		perror("Error opening heredoc_tmp.txt for reading");
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

