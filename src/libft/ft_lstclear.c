/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:01:16 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:24 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*now_pt;
	t_list	*next_pt;

	next_pt = NULL;
	if (lst != NULL && *lst != NULL)
	{
		now_pt = (*lst);
		next_pt = (*lst)->next;
	}
	else
		return ;
	while (1)
	{
		ft_lstdelone(now_pt, del);
		if (next_pt == NULL)
			break ;
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	*lst = NULL;
	return ;
}

// #include "libft.h"
// static void	del2(void* content)
// {
// 	free(content);
// 	return ;
// }

// int	main(){
// 	char *test_value1 = ft_strdup("Hello World");
// 	char *test_value2 = ft_strdup("zzzzzzz");
// 	t_list	*test1 = ft_lstnew((void *) "abcdefg");
// 	t_list	*test2 = ft_lstnew((void *) "hijklmn");
// 	t_list	*test3 = ft_lstnew(test_value1);
// 	t_list	*test4 = ft_lstnew(test_value2);
// 	ft_lstadd_front(&test1, test2);
// 	ft_lstadd_front(&test2, test3);
// 	ft_lstadd_back(&test1, test4);
// 	ft_lstclear(&test3, del2);
// 	free(test1);
// 	free(test2);
// }
