/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:18:30 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/13 13:27:50 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*temp;

	i = ft_strlen(s);
	if (len + start > i)
		len = ft_strlen(s);
	if (start >= i)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	temp = str;
	i = 0;
	while (*(s + start) && i++ < len)
	{
		*str++ = *(s + start);
		start++;
	}
	*str = '\0';
	return (temp);
}
