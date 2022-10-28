/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:10 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/12 12:12:06 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	i;
	size_t	l;

	n = ft_strlen(src);
	i = ft_strlen(dst);
	l = dstsize;
	if (dstsize < i || !dstsize)
		return (l + n);
	while (--dstsize > i && *src && dstsize)
		*(i + dst++) = *(src++);
	*(dst + i) = 0;
	return (i + n);
}
/*
int main()
{
    char d[30];
    ft_memset(d,0,30);
    int i= ft_strlcat(d,"123",0);
    printf("%d",i);
    printf("%s",d);
}*/