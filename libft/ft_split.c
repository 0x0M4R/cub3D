/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:19:26 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/13 11:16:42 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_ret_empty(void)
{
	char	**empty;

	empty = malloc(sizeof(char *));
	*empty = 0;
	return (empty);
}

static int	ft_count_sep(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		if (*s == c && *s)
		{
			i++;
			s++;
			while (*s == c && *s)
				s++;
			continue ;
		}
		s++;
	}
	s--;
	if (*s != c && *s)
		i++;
	return (i);
}

static int	ft_count_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static void	ft_copyword(char const *s, char **arr, int i, int j)
{
	int	k;

	k = -1;
	while (k++ < i)
		arr[j][k] = *(s + k);
	arr[j][k] = '\0';
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;
	int		k;

	if (*s == '\0')
		return (ft_ret_empty());
	k = ft_count_sep(s, c);
	arr = malloc(sizeof(char *) * (k + 1));
	if (!arr)
		return (NULL);
	arr[k] = 0;
	j = -1;
	while (j++ < k - 1)
	{
		while (*s == c && *s)
			s++;
		i = ft_count_word(s, c);
		arr[j] = malloc(sizeof(char) * (i + 1));
		if (!(arr[j]))
			return (NULL);
		ft_copyword(s, arr, i - 1, j);
		s += i;
	}
	return (arr);
}
/*
int main()
{
	char **r=ft_split("", 'z');
	int i=0;
	printf("%s",r[i]);
}*/