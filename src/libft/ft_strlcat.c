/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:10:10 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 18:10:10 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (src_len);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + src_len);
	c = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}

// int main()
// {
//     char  *src = "the cake is a lie !\0I'm hidden lol\r\n";
//     char dest[50]  = "there is no stars in the sky";
//     char dest2[50]  = "there is no stars in the sky";
// 	size_t size = ft_strlen(src) + 4;

//     printf("%zu\n", ft_strlcat(dest,src, size));
//     printf("%zu\n", strlcat(dest2,src, size));

//     return (0);
// }