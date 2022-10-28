/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:19:07 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/12 12:13:11 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(src);
	if (!dstsize)
		return (i);
	else if (dstsize <= i)
	{
		ft_memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	else
	{
		ft_memmove(dst, src, i);
		dst[i] = '\0';
	}
	return (i);
}
/*
int main()
{
    char s[]="hihihi";
    char d[10];
    ft_memset(d,'A',10);
    int i=ft_strlcpy(d,s,6);
    printf("%d\n",i);
    printf("%d\n",ft_strlen(s));
    printf("%s\n",s);
    printf("%s\n",d);
    
    
}*/