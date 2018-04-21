/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:10:45 by mbenkara          #+#    #+#             */
/*   Updated: 2018/03/30 17:27:15 by mbenkara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_recursion(t_opt arg, char *path)
{
	t_elem	*files;
	DIR		*dir;

	files = NULL;
	ft_putchar('\n');
	ft_putstr(path);
	ft_putstr(":\n");
	if ((dir = opendir(path)) != NULL)
	{
		while (elemget(&files, readdir(dir), \
					ft_strjoin(path, "/"), arg) != 0)
			;
		closedir(dir);
		if (files)
			display_file(arg, files, 1);
		files = NULL;
	}
	else
		basicerror("ft_ls: ", path, 0);
}

void	recursion(t_opt arg, t_elem *files)
{
	t_elem	*cur;

	cur = files;
	while (cur)
	{
		if (cur->name && cur->path && \
				S_ISDIR(cur->st_mode) && \
				ft_strcmp(".", cur->name) && \
				ft_strcmp("..", cur->name) && \
				!(arg.a == 0 && cur->name[0] == '.'))
			do_recursion(arg, cur->path);
		cur = cur->next;
	}
}

int		cmp_alpha(t_elem *elem1, t_elem *elem2)
{
	return (ft_strcmp(elem1->name, elem2->name));
}

int		cmp_time(t_elem *elem1, t_elem *elem2)
{
	return (elem1->date < elem2->date);
}

int		one_of(char c, char *str)
{
	int		i;

	if (str == NULL || c == '\0')
		return (0);
	i = -1;
	while (str[++i])
		if (c == str[i])
			return (1);
	return (0);
}
