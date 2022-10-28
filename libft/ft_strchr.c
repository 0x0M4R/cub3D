/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:19:22 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/12 10:35:34 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	j;

	j = ft_strlen(s) + 1;
	while (j--)
	{
		if (*s == (const char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
