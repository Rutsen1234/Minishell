/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:05 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/16 01:13:37 by haeltahi         ###   ########.fr       */
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
