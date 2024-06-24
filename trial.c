# define GREEN "\e[1;32m"
# define RESET "\e[0m"
#include <string.h>
#include <unistd.h>
int main() {



    write(1, GREEN, strlen(GREEN));
    write(1, "minishell$ ", strlen("minishell$ "));
    write(1, RESET, strlen(RESET));
}