/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:47:54 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 11:47:54 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	lst->content = (char *) "hello";
// 	lst->next = NULL;
// 	t_list *new = malloc(sizeof(t_list));
// 	new->content = (char *) "world";
// 	new->next = NULL;
// 	// lst = new;
// 	ft_lstadd_front(&lst, new);
// 	t_list *curr;
// 	curr = lst;
// 	while (curr != NULL)
// 	{
// 		printf("%s\n", (char *)(curr->content));
// 		curr = curr->next;
// 	}
// }
