/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:29:18 by oabdalla          #+#    #+#             */
/*   Updated: 2022/10/27 12:21:52 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 30
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*ft_gnljoin(char *s1[], char *s2);
int		ft_strchr_i(const char *s, int c);
char	*ft_strldup(const char *s1, int i);

#endif