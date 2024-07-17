/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:52:14 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 16:52:14 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SIZE_ARRAY 7

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n--)
	{
		((unsigned char *)s)[i++] = c;
	}
	return (s);
}

// int main()
// {
//     char arr[SIZE_ARRAY] = "ABCD";
//     printf("%s\n", arr);
//     ft_memset(arr,'0', sizeof(arr));
//     printf("%s\n", arr);
//     return 0;
// }