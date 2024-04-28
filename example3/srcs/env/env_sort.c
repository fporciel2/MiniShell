#include "minishell.h"

static t_env	*merge(t_env *list1, t_env *list2)
{
	if (list1 == NULL)
		return (list2);
	if (list2 == NULL)
		return (list1);
	if (ft_strncmp(list1->name, list2->name, ft_strlen(list1->name)) < 0)
	{
		list1->next = merge(list1->next, list2);
		return (list1);
	}
	else
	{
		list2->next = merge(list1, list2->next);
		return (list2);
	}
}

static void	split_env(t_env *source, t_env **front, t_env **back)
{
	t_env	*fast;
	t_env	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

static void	merge_sort(t_env **headRef)
{
	t_env	*head;
	t_env	*a;
	t_env	*b;

	head = *headRef;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split_env(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*headRef = merge(a, b);
}

t_env	*env_sort(t_env *env_head)
{
	t_env	*sorted_env;

	sorted_env = env_cpy(env_head);
	if (!sorted_env)
		return (NULL);
	merge_sort(&sorted_env);
	return (sorted_env);
}
