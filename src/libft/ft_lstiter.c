/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 07:13:48 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:28 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*now_pt;
	t_list	*next_pt;

	if (f == NULL || lst == NULL)
		return ;
	now_pt = lst;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		f(now_pt->content);
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	f(now_pt->content);
	return ;
}

// #include "libft.h"
// void	mapfunc(void* content)
// {
// 	ft_bzero(content, ft_strlen((char *) content));
// 	return ;
// }
// int	main(){
// 	char *test_value1 = ft_strdup("abcdefg");
// 	char *test_value2 = ft_strdup("hijklmn");
// 	char *test_value3 = ft_strdup("Hello World");
// 	char *test_value4 = ft_strdup("zzzzzzz");
// 	t_list	*test1 = ft_lstnew(test_value1);
// 	t_list	*test2 = ft_lstnew(test_value2);
// 	t_list	*test3 = ft_lstnew(test_value3);
// 	t_list	*test4 = ft_lstnew(test_value4);
// 	ft_lstadd_front(&test1, test2);
// 	ft_lstadd_front(&test2, test3);
// 	ft_lstadd_back(&test1, test4);
// 	ft_lstiter(test1, mapfunc);
// 	free(test_value1);
// 	free(test_value2);
// 	free(test_value3);
// 	free(test_value4);
// 	free(test1);
// 	free(test2);
// 	free(test3);
// 	free(test4);
// }
