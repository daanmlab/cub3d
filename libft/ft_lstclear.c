/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:37:37 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 15:10:07 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

// t_list *strtab_to_list(char *a[])
// {
// 	int i;
// 	t_list *ret;
// 	t_list *curr;

// 	i = 1;
// 	ret = ft_lstnew(ft_strdup(a[0]));
// 	curr = ret;
// 	while (a[i])
// 	{
// 		curr->next = ft_lstnew(ft_strdup(a[i]));
// 		curr = curr->next;
// 		i++;
// 	}
// 	return (ret);
// }
// #include <stdio.h>
// void ft_printlst(t_list *lst)
// {
// 	int i;
// 	t_list *curr;

// 	i = 0;
// 	curr = lst;
// 	if (!lst)
// 		printf("NULL");
// 	while (curr->next)
// 	{
// 		printf("%d : %s", i, (char *)curr->content);
// 		curr = curr->next;
// 		i++;
// 	}
// }

// int main(void)
// {
// 	char *test[] = {
// 		ft_strdup("abc"),
// 		ft_strdup("def"),
// 		ft_strdup("ghi"),
// 		ft_strdup("jkl"),
// 	};
// 	t_list *testlst = strtab_to_list(test);
// 	ft_lstclear(&testlst, free);
// 	ft_printlst(testlst);
// 	return (0);
// }