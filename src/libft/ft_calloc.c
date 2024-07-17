/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:39:58 by Degef             #+#    #+#             */
/*   Updated: 2022/12/28 13:57:10 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count >= 65535 && size >= 65535)
		return (0);
	p = malloc (count * size);
	if (!p)
		return (0);
	ft_bzero(p, (count * size));
	return (p);
}

// int main()
// {
// 	int i = 100;
// 	int m = 4;
// 	printf("%s\n", ft_calloc(i, m));
// 	return (0);
// }