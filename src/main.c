#include <stdio.h>

int main(int ac, char **av, char **env)
{
    (void)ac; 
    (void)av;  
   
    ft_minishell(env);
    //signal()

    while(1)
    {
        int i =0;
        printf("%i", i);
        i++;
    }
}
