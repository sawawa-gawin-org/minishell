/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:05:36 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*next_pt;

	if (lst == NULL)
		return (0);
	counter = 1;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		counter += 1;
		next_pt = next_pt->next;
	}
	return (counter);
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

// 	int	cnt = ft_lstsize(test1);
// 	free(test1);
// 	free(test2);
// 	free(test3);
// 	free(test4);
// }
