/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:39 by lkoc              #+#    #+#             */
/*   Updated: 2024/03/21 12:08:41 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *buff);
char	*ft_join_iterate(char *str, char *s1, char *buff);
void	*ft_calloc_gnl(size_t nmemb, size_t size);

#endif