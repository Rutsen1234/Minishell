/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:49 by Degef             #+#    #+#             */
/*   Updated: 2022/12/27 14:03:13 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*p;
	char	*dup;

	size = ft_strlen(s1);
	dup = (char *)malloc(size * sizeof(char) + 1);
	if (!dup)
		return (0);
	p = dup;
	while (*s1)
	{
		*p = *s1;
		p++;
		s1++;
	}
	*p = '\0';
	return (dup);
}

// int	main(void)
// {
// 	char	*str = "Hello";

// 	printf("%s\n", ft_strdup(str));
// 	return (0);
// }