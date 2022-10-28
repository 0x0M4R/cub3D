/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:18:46 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/13 12:42:11 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_checkset(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*temp;
	char			*s2;

	i = 0;
	if (*s1 == '\0')
		return (ft_strdup(""));
	if (*set == '\0')
		return (ft_strdup(s1));
	j = (int)ft_strlen(s1) - 1;
	temp = (char *)s1;
	while (ft_checkset(set, temp[j]) && j)
		j--;
	while (ft_checkset(set, temp[i]))
		i++;
	if (j < i)
		return (ft_strdup(""));
	s2 = malloc(sizeof(char) * (j - i + 2));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, temp + i, j - i + 2);
	return (s2);
}
