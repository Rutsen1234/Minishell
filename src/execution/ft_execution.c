#include "../../headers/execution.h"

void	ft_execve(t_simple_cmd *cmd, char **args, char **list)
{
	if (execve(cmd->command, args, list) == -1)
	{
		char *error = ft_strjoin(": ", strerror(errno));
		ft_put_err(cmd->command, error, errno);
		free(error);
		exit(errno);
	}
}

int ft_exec(t_simple_cmd *cmd, t_env **head)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        return ft_put_err("fork: ", "Fork failed", errno);
    }
    else if (pid == 0)
    {
        ft_execve(cmd, ft_args_to_arr(cmd), ft_list_to_arr(head));
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            return ft_put_err("waitpid: ", "Wait failed", errno);
        }

        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGQUIT)
                write(STDOUT_FILENO, "Quit: 3\n", 8);

            return 128 + WTERMSIG(status);
        }
    }

    return 77; 
}

void	ft_exec_file(t_simple_cmd *cmd, t_env **head, char *path, int *status)
{
	struct stat buf;
	char *full_path = ft_join_path(path, cmd->command);

	stat(full_path, &buf);
	if ((buf.st_mode & S_IXUSR) && (buf.st_mode & S_IFREG) && *status == -77)
	{
		free(cmd->command);
		cmd->command = ft_strdup(full_path);
		*status = ft_exec(cmd, head);
	}
	free(full_path);
}


int	ft_is_builtins(t_simple_cmd *cmd, t_env **head)
{
	if (!(ft_strcmp(cmd->command, "echo"))
		|| !(ft_strcmp(cmd->command, "ECHO")))
		return (ft_echo(cmd->args));
	else if (!(ft_strcmp(cmd->command, "cd"))
		||!(ft_strcmp(cmd->command, "CD")))
		return (ft_cd(cmd->args, head));
	else if (!(ft_strcmp(cmd->command, "pwd"))
		|| !(ft_strcmp(cmd->command, "PWD")))
		return (ft_pwd(head));
	else if (!(ft_strcmp(cmd->command, "env"))
		|| !(ft_strcmp(cmd->command, "ENV")))
		return (ft_env(head));
	else if (!(ft_strcmp(cmd->command, "export"))
		|| !(ft_strcmp(cmd->command, "EXPORT")))
		return (ft_export(head, cmd->args));
	else if (!(ft_strcmp(cmd->command, "unset"))
		|| !(ft_strcmp(cmd->command, "UNSET")))
		return (ft_unset(cmd->args, head));
	else if (!(ft_strcmp(cmd->command, "exit"))
		|| !(ft_strcmp(cmd->command, "EXIT")))
		return (ft_exit(cmd->args));
	else
		return (ft_check_path(cmd, head));
}

int	ft_execute(t_pipe_line *cmd, t_env **head)
{
	t_mini	mini;

	mini.flag = 0;
	mini.red_fd[0] = 0;
	mini.red_fd[1] = 0;
	ft_putstr_fd(BLUE, 1);
	ft_do_backups(1);
	if (cmd->child->redirections != NULL)
	{
		if (ft_redirection(&mini, cmd->child->redirections))
		{
			ft_do_backups(0);
			return (1);
		}
	}
	if (cmd->child->command == NULL && cmd->child->redirections == NULL)
		return (ft_put_err("\0", ": command not found", 127));
	if (cmd->simple_cmd_count > 1)
		mini.ret = ft_pipe(&mini, cmd, head);
	else if (cmd->child->command != NULL)
		mini.ret = ft_is_builtins(cmd->child, head);
	ft_do_backups(0);
	return (mini.ret);
}
