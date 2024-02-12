/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:55:16 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 17:58:41 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
	{
		ft_lstdelone(new, del);
		return (NULL);
	}
	curr = new;
	while (lst->next)
	{
		lst = lst->next;
		curr->next = ft_lstnew(f(lst->content));
		if (!curr->next)
		{
			ft_lstclear(&curr, del);
			return (NULL);
		}
		curr = curr->next;
	}
	return (new);
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
// 	while (curr->next)
// 	{
// 		printf("%d : %s\n", i, (char *)curr->content);
// 		curr = curr->next;
// 		i++;
// 	}
// }

// void *test_fn(void *v)
// {
//     return (ft_split(v, ' ')[1]);
// }

// int main(void)
// {
// 	char *test[] = {
// 		"ab c",
// 		"de f",
// 		"gh i",
// 		"jk l"
// 	};
// 	t_list *testlst = strtab_to_list(test);
//     ft_printlst(ft_lstmap(testlst, test_fn, free));
// 	return (0);
// }