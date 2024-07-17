/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:45:14 by Degef             #+#    #+#             */
/*   Updated: 2022/12/24 11:45:14 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = ft_lstlast(*lst);
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	if (lst == NULL)
// 		exit(1);
// 	lst->content = (char *)"15";
// 	lst->next = NULL;
// 	t_list *new = malloc(sizeof(t_list));
// 	if (new == NULL)
// 		exit(2);
// 	new->content = (char *)"16";
// 	new->next = NULL;
// 	ft_lstadd_back(&lst, new);
// 	t_list *curr = lst;
// 	while (curr)
// 	{
// 		printf("%s\n", (char *)curr->content);
// 		curr = curr->next;
// 	}
// }
