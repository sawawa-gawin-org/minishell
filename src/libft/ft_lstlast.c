/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:35:36 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:30 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*now_pt;
	t_list	*next_pt;

	if (lst == NULL)
		return (lst);
	now_pt = lst;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	return (now_pt);
}

// #include "libft.h"
// static void	del2(void* content)
// {
// 	content = NULL;
// 	return ;
// }
// int	main(){
// 	t_list	*test1 = ft_lstnew((void *) "abcdefg");
// 	t_list	*test2 = ft_lstnew((void *) "hijklmn");
// 	t_list	*test3 = ft_lstnew((void *) "opqrst");
// 	// ft_lstadd_front(&test1, test2);
// 	// ft_lstadd_front(&test3, test1);

// 	t_list	*pt = ft_lstlast(test2);
// 	t_list	*null =  NULL;
// 	pt = ft_lstlast(null);
// 	ft_lstadd_front(&null, test1);
// 	pt = ft_lstlast(null);
// 	ft_lstclear(&test3, del2);
// }
