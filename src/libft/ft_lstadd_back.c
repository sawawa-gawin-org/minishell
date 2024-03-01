/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:45:38 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_pt;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_pt = ft_lstlast(*lst);
	(*last_pt).next = new;
	return ;
}

// int	main(){
// 	t_list	*test0 =  NULL;
// 	t_list	*test1 = ft_lstnew((void *) "abcdefg");
// 	t_list	*test2 = ft_lstnew((void *) "hijklmn");
// 	t_list	*test3 = ft_lstnew((void *) "opqrstu");
// 	t_list	*test4 = ft_lstnew((void *) "zzzzzzz");

// 	ft_lstadd_back(&test0, test1);
// 	ft_lstadd_back(&test0, test2);
// 	ft_lstadd_back(&test0, test3);
// 	ft_lstadd_back(&test0, test4);
// 	ft_lstadd_back(NULL, test4);
// 	free(test1);
// 	free(test2);
// 	free(test3);
// 	free(test4);
// }
