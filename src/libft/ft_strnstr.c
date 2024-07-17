/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:35:52 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 18:35:52 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				j;
	int				s2_len;

	i = 0;
	s2_len = ft_strlen(s2);
	if (!s1 && n == 0)
		return (0);
	if (!s2_len)
		return ((char *)(s1));
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] != '\0' && s1[i + j] == s2[j] && ((i + j) < n))
			{
				if (s2[j + 1] == '\0')
					return ((char *)(s1 + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// int main ()
// {

//     char * big = "xlrolfol";
//     char *little = "rolf";
//     // printf("%s\n", big);
//     printf("%s\n", ft_strnstr(big, little, 15));
//     printf("%s\n", strnstr(big, little, 15));
//     return (0);
// }