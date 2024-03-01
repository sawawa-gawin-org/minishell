/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:20:18 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:47:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del == NULL || lst == NULL)
		return ;
	if (lst->content != NULL)
	{
		del(lst->content);
	}
	free(lst);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// static void	del(void* content)
// {
// 	free(content);
// 	return ;
// }
// #include "libft.h"
// int	main(){
// 	char *test_value = ft_strdup("Hello World");
// 	t_list	*test3 = ft_lstnew(test_value);
// 	t_list	*test5 = ft_lstnew(NULL);
// 	ft_lstdelone(NULL, NULL);
// 	ft_lstdelone(test3, del);
// 	ft_lstdelone(test5, del);
// }
