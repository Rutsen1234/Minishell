/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:07:15 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/13 12:26:51 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

int	ft_create_fd_pipe(t_pipe_line *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	mini->fd = malloc(sizeof(int) * cmd->simple_cmd_count * 2);
	mini->pid = malloc(sizeof(int) * (cmd->simple_cmd_count + 1));
	if (!mini->fd)
		return (ft_put_err("malloc", ": malloc failed", 1));
	while (i < cmd->simple_cmd_count)
	{
		if (pipe(mini->fd + i * 2) < 0)
			return (ft_put_err("pipe", ": couldn't create pipe", 1));
		i++;
	}
	return (0);
}

void	ft_pipe_fork(t_simple_cmd *cmd, t_env **head, t_mini *mini,
		int *command)
{
	int	i;

	i = 0;
	g_vars.infork = YES;
	if (cmd->next && dup2(mini->fd[*command + 1], STDOUT_FILENO) < 0)
		exit(ft_put_err("dup2", ": couldn't clone the fd", 1));
	if (*command != 0 && dup2(mini->fd[*command - 2], STDIN_FILENO) < 0)
		exit(ft_put_err("dup2", ": couldn't clone the fd1", 1));
	while (i < mini->simple_cmd_count * 2)
	{
		close(mini->fd[i]);
		i++;
	}
	mini->ret = ft_is_builtins(cmd, head);
	exit(mini->ret);
}

int	ft_close_fd(t_pipe_line *cmd, t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd->simple_cmd_count * 2)
	{
		close(mini->fd[i]);
		i++;
	}
	i = 0;
	while (i < cmd->simple_cmd_count + 1)
	{
		waitpid(mini->pid[i], &status, 0);
		mini->ret = WEXITSTATUS(status);
		i++;
	}
	free(mini->fd);
	free(mini->pid);
	return (mini->ret);
}

int	ft_pipe(t_mini *mini, t_pipe_line *cmd, t_env **head)
{
	t_simple_cmd	*tmp;
	int				command;
	int				k;

	tmp = cmd->child;
	command = 0;
	k = 0;
	cmd->simple_cmd_count--;
	mini->simple_cmd_count = cmd->simple_cmd_count;
	if (ft_create_fd_pipe(cmd, mini))
		return (1);
	while (tmp)
	{
		mini->pid[k] = fork();
		if (mini->pid[k] == -1)
			return (ft_put_err("fork", ": couldn't fork properly\n", errno));
		else if (mini->pid[k] == 0)
			ft_pipe_fork(tmp, head, mini, &command);
		tmp = tmp->next;
		command += 2;
		ft_do_backups(0);
		k++;
	}
	return (ft_close_fd(cmd, mini));
}

int	ft_file_err(char *file_name)
{
	struct stat	buf;

	if (stat(file_name, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (ft_put_err(file_name, ": Is a directory", 1));
		if ((buf.st_mode & S_IXUSR) == 0)
			return (ft_put_err(file_name, ": Permission denied", 1));
	}
	return (ft_put_err(file_name, ": No such file or directory", 1));
}
