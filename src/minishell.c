#include "../headers/minishell"

void show_prompt()
{
    write(1, GREEN, ft_strlen(GREEN));
    write(1, "minishell$", ft_strlen("minishell$"));
    write(1, RESET, ft_strlen(RESET));
}
void ft_init_minishell(char **last_arg_exit_status, char **line, t_pipeline **current_pipeline, t_env **env_list)
{
    g_vars.cmd = NULL;  //global variable that likely serves to store the current command or a recent command
    *current_pipeline=NULL;
    last_arg_exit_status[0]=ft_strdup("0");//Defaulting past exit status success unless specified otherwise.
    *line= NULL;
    *env_list=NULL;
}


void ft_minishell(char **env)
{
    t_pipeline *current_pipeline;
    t_env       *env_list;
    char        *line;
    int status;
    static char     *last_arg_exit_status[2];


    status=0;
    ft_init_minishell(last_arg_exit_status, &line, &current_pipeline, &env_list);
    signal(SIGINT,ft_signal_handler);
    signal(SIGQUIT,ft_signal_handler);
    ft_init_env(&env_list, env);
    while (1)
    {
        show_prompt();
        micro_readline(&line, &status);
    }
}