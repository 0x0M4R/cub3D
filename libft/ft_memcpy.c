/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:20:55 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/03 14:24:58 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n-- && (dst || src))
		*(unsigned char *)(dst + n) = *(unsigned char *)(src + n);
	return (dst);
}
/*
int main()
{
	char d[22];
	char s[]="test basic du memcpy !";
	printf("%s\n",d);
	printf("%s\n",s);
	printf("%s\n",ft_memcpy(((void *)0), ((void *)0), 3));
	printf("%s\n",d);
	printf("%s\n",s);
	printf("%s\n",memcpy(((void *)0), ((void *)0), 3));
}*/