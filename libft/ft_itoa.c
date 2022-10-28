/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:55:37 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/07 17:56:05 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countdigits(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	char	*ft_putstr(char *str, int n, int i)
{
	int	digit;

	while (n > 0)
	{
		digit = n % 10;
		str[--i] = digit + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = ft_countdigits(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_memset(str, '0', i);
	str[i] = '\0';
	if (n < 0)
	{
		*str = '-';
		n *= -1;
	}
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
	}
	return (ft_putstr(str, n, i));
}
/*
int main()
{
	printf("%s", ft_itoa(-0));
	printf("%s", ft_itoa(1234));
}*/