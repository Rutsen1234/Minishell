// // # define GREEN "\e[1;32m"
// // # define RESET "\e[0m"
// #include <string.h>
//  #include <unistd.h>
// #include <ctype.h>
// // int main() {

// #include "src/libft/libft.h"

// //     write(1, GREEN, strlen(GREEN));
// //     write(1, "minishell$ ", strlen("minishell$ "));
// //     write(1, RESET, strlen(RESET));
// // }

// #include <stdio.h>
// #include <termcap.h>
// #include <stdlib.h>

// void	ft_get_cursor_position(int *x, int *y)
// {
// 	static char	c[20];
// 	int			i;
// 	int			first;


// 	i = 0;
// 	first = 0;
// 	write(0, "\033[6n", 4);
	

// 	read(0, c, 19);
// 	printf("hi\n");
// 	fflush(stdout);
	
// 	while (c[i])
// 	{
		
// 		if (first == 0 && isdigit(c[i]))
// 		{
// 			*x = atoi(c + i);
// 			while (c[i] != ';')
// 				i++;
// 			first = 1;
//                 printf("hwew%i %i\n",*x, *y);

// 		}
// 		else if (first == 1 && isdigit(c[i]))
// 		{
// 			*y = atoi(c + i);
// 			first = 2;
// 		}
// 		i++;
// 	}
// }
// int main() {
//     // char *term_type = getenv("TERM");
//     // int columns = tgetnum("co");
//     // int lines = tgetnum("li");

//     // if (columns > 0 && lines > 0) {
//     //     printf("Terminal size: %d columns x %d lines.\n", columns, lines);
//     // } else {
//     //     printf("Failed to retrieve terminal size.\n");
//     // }
//     	ft_get_cursor_position(0,0);


//     return 0;
// }

#include <stdio.h>
#include <unistd.h>

void get_cursor_position()
{
    char response[20]; // Buffer to hold the response from terminal
    write(0, "\033[6n", 4); // Send the escape sequence to get cursor position
    read(0, response, 19); // Read the response into 'response' buffer
    printf("Terminal response: %s\n", response); // Display the response
}

int main()
{
    get_cursor_position();
    return 0;
}
