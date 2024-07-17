#include "libft.h"

int before_equal(char *str, char c)
{
    int i = 0;
    while (str[i] && str[i] != c)
        i++;
    return i;
}

void after_equal(char *str, char **s, int i)
{
    int j = 0;
  
    if (str[i] == '=' || str[i + 1] == '\0')
        s[1][0] = '\0';
    else if (str[i] == '\0')
    {
        free(s[1]);
        s[1] = NULL;
    }
    else
    {
        j = 0;
        while (str[i])
        {
            s[1][j] = str[i];
            j++;
            i++;
        }
        s[1][j] = '\0';
    }
}

char **my_split(char *str)
{
    int i = 0, j = 0;
    i = before_equal(str, '=');

    char **s = malloc(sizeof(char *) * 2);
    s[0] = malloc(sizeof(char) * (i + 1));
    s[1] = malloc(sizeof(char) * (ft_strlen(str) - i + 1));

    while (str[j] && str[j] != '=')
    {
        s[0][j] = str[j];
        j++;
    }
    s[0][j] = '\0';
    after_equal(str, s, j);
    return s;
}
