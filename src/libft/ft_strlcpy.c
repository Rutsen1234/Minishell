/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:23:39 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 18:23:39 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!src && !size)
		return (0);
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	while ((i + 1 < size) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

// int main()
// {
//     char dest[15]  = "hello";
//     char src[15] = "GeeksforGeeks";
//     printf("%zu\n", ft_strlcpy(dest, src, 16));
//     printf("%lu\n", strlcpy(dest, src, 15));
// 	printf("%s\n", dest);
//     return (0);
// }