/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:29:18 by oabdalla          #+#    #+#             */
/*   Updated: 2021/12/06 16:16:31 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 30
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_strchr_i(const char *s, int c);
char	*ft_strldup(const char *s1, int i);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif