

#include "../../headers/execution.h"
int ft_count_list(t_env **head)
{
    int count = 0;
    t_env *current = *head;
    while (current)
    {
        current = current->next;
        count++;
    }
    return count;
}

void ft_free_list(char **list)
{
    int i = 0;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
    free(list);
}

char **ft_args_to_arr(t_simple_cmd *cmd)
{
    t_args *arg_node = cmd->args;
    int num_args = ft_count_args(&arg_node) + 1;
    char **args = malloc((num_args + 1) * sizeof(char *));
    args[0] = ft_strdup(cmd->command);

    int i = 1;
    while (arg_node)
    {
        if (arg_node->value == NULL && arg_node->inside_quotes == 2)
            arg_node->value = ft_strdup("");
        args[i] = ft_strdup(arg_node->value);
        i++;
        arg_node = arg_node->next;
    }
    args[i] = NULL;
    return args;
}

void ft_init_env(t_env **head, char **env)
{
    int i = 0;
    while (env[i])
    {
        char **var = splitforenv(env[i]);
        t_env *new_node = ft_create_node(var[0], var[1]);

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
