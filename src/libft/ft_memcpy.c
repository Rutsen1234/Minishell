/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:19:56 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 14:19:56 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;
	int		i;

	i = 0;
	csrc = (char *)src;
	cdest = (char *)dest;
	if (!cdest && !csrc)
		return (0);
	while (n--)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (cdest);
}

// int main()
// {
// char csrc[] = "Hello World";
// char cdest[20];
// ft_memcpy(&cdest, &csrc, ft_strlen(csrc)+1);
// printf("Copied string is %s", cdest);
// return (0);

// char csrc[100] = "Geeksfor";
// printf("%s", csrc);

// memcpy(csrc+5, csrc, strlen(csrc)+1);
// printf("%s", csrc);
// return 0;
// }