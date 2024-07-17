/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:25 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 12:09:25 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const	char *nptr)
{
	int	result;
	int	sign;
	int	num;

	sign = 1;
	result = 0;
	while (nptr && ((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (nptr && *nptr >= '0' && *nptr <= '9')
	{
		num = *nptr - '0';
		result *= 10;
		result += num;
		nptr++;
	}
	result *= sign;
	return (result);
}

// int main()
// {
//     char *num = "           1234m234";
//     printf ("%d\n", ft_atoi(num));
//     return (0);
// }