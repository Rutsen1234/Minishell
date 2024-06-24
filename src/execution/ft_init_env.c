// #include <unistd.h>
// #include <string.h>

// #define GREEN "\033[0;32m"
// #define RESET "\033[0m"

// size_t ft_strlen(const char *str) {
//     size_t len = 0;
//     while (str[len] != '\0')
//         len++;
//     return len;
// }

// void show_prompt(void) {
//     write(1, GREEN, ft_strlen(GREEN));              // Change color to green
//     write(1, "minishell$ ", strlen("minishell$ ")); // Print the prompt
//     write(1, RESET, ft_strlen(RESET));              // Reset color to default
// }

// int main() {
//     show_prompt();
//     return 0;
// }

void ft_init_env(t_env **head, char **env)
{
    t_env *new_node;
    char **var;
    int i;

    new_node=NULL;
    i=0;
    while (env[i])
    {
        var = ft_split(env[i]);
        new_node=ft_create_node(var[0], var[1]);
        if (!head)
            head = &new_node;
        else
            ft_add_to_list(head, new_node);
        free(var[0]);
        free(var[1]);
        free(var);
    }
}