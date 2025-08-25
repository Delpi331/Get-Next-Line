/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-pin <ddel-pin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:19:19 by ddel-pin          #+#    #+#             */
/*   Updated: 2024/11/29 17:20:27 by ddel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *str)
{
	const char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		s++;
	return (s - str);
}

void	sfree(char **a, char *b)
{
	if (*a)
		free(*a);
	if (b)
		*a = b;
}

char	*strnjoin(char *s1, char *s2, size_t n)
{
	char	*p;
	size_t	len1;
	size_t	i;

	len1 = ft_strlen(s1);
	p = malloc(len1 + n + 1);
	if (!p)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			p[i++] = *(s1++);
	while (*s2 && i - len1 < n)
		p[i++] = *(s2++);
	p[i] = '\0';
	return (p);
}
