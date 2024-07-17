/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:01:23 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 14:01:23 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return ((*(unsigned char *)s1 - *(unsigned char *)s2));
		s1++;
		s2++;
	}
	return (0);
}

// int main()
// {
//     char *s1 = "Ada";
//     char *s2 = "Aaa";
//     printf("%d\n", memcmp(s1, s2, 5));
//     printf("%d\n", ft_memcmp(s1, s2, 5));
//     return (0);
// }