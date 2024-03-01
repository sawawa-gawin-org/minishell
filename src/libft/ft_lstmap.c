/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 07:31:57 by saraki            #+#    #+#             */
/*   Updated: 2023/10/30 21:20:34 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exit_iter(t_list *new, t_list *initial, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*now_pt;
	t_list	*new_pt;
	t_list	*initial_pt;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	initial_pt = ft_lstnew(f(lst->content));
	if (initial_pt == NULL)
		return (NULL);
	now_pt = lst->next;
	while (now_pt != NULL)
	{
		new_pt = ft_lstnew(f(now_pt->content));
		if (exit_iter(new_pt, initial_pt, del))
			return (NULL);
		ft_lstadd_back(&initial_pt, new_pt);
		now_pt = now_pt->next;
	}
	return (initial_pt);
}

static int	exit_iter(t_list *new, t_list *initial, void (*del)(void *))
{
	if (new == NULL)
	{
		ft_lstclear(&initial, del);
		return (1);
	}
	return (0);
}

// #include "libft.h"
// void	*mapfunc2(void* content)
// {
// 	void	*result;
// 	size_t	len;

// 	len = ft_strlen((char *) content);
// 	result = ft_calloc(sizeof(char), len + 1);
// 	result = ft_memcpy(result, content, len + 1);
// 	ft_bzero(result, len);
// 	return (result);
// }

// static void	del3(void* content)
// {
// 	free(content);
// 	return ;
// }

// int	main(){
// 	char *test_value1 = ft_strdup("abcdefg");
// 	char *test_value2 = ft_strdup("hijklmn");
// 	char *test_value3 = ft_strdup("Hello World");
// 	char *test_value4 = ft_strdup("zzzzzzz");
// 	t_list	*test1 = ft_lstnew(test_value1);
// 	ft_lstadd_back(&test1, ft_lstnew(test_value2));
// 	ft_lstadd_back(&test1, ft_lstnew(test_value3));
// 	ft_lstadd_back(&test1, ft_lstnew(test_value4));

// 	t_list	*result;
// 	result = (t_list *) ft_lstmap(test1, mapfunc2, del3);

// 	ft_lstclear(&test1, del3);
// 	if (result != NULL)
// 		ft_lstclear(&result, del3);
// }
