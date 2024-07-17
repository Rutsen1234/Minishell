/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:45:16 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 18:45:16 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c >= 256)
		c = c % 256;
	while (s[i] != '\0')
		i++;
	if (c == '\0')
		return ((char *)(s + i));
	while (i--)
	{
		if (s[i] == c)
			return ((char *)(s + i));
	}
	return (0);
}

// int main()
// {
//     char *s = "hello0";
//     char c = (char)608;

//     printf("%s\n", ft_strrchr(s, c));
//     printf("%s\n", strrchr(s, c));
//     return (0);
// }