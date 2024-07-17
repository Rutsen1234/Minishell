/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:44:01 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 13:44:01 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findsize(int n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	while (n && ++size)
		n = n / 10;
	return (size);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*str;
	const char	*digits = "0123456789";

	size = 1;
	if (n != 0)
		size = findsize(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	str[size] = 0;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		if (n > 0)
			str[--size] = digits[n % 10];
		else
			str[--size] = digits[n % 10 * -1];
		n /= 10;
	}
	return (str);
}

// int main()
// {
//     printf("%s\n", ft_itoa(0));
// 	printf("%d\n", findsize(0));
//     return (0);
// }