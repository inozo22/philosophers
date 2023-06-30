#include <stdio.h>
#include <stdlib.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;


t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	freemem(t_list *list)
{
	free (list);
	list = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}


void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst && *lst)
	{
		ft_lstclear(&(*lst)->next, del);
		ft_lstdelone(*lst, del);
		*lst = 0;
	}
}

int	main(void)
{
	t_list	*list;

	list = ft_lstnew("dadada");

	printf("List1:		%p\n", list);
	printf("List2:		%p\n", &list);
	printf("List content3:	%p\n", list->content);
	printf("List content4:	%p\n", &list->content);
//	freemem(list);
//	free (list);
//	list = NULL;
	ft_lstclear(&list, NULL);
	printf("List1:		%p\n", list);
	printf("List2:		%p\n", &list);
	printf("List content3:	%p\n", list->content);
	printf("List content4:	%p\n", &list->content);
	return 0;
}


