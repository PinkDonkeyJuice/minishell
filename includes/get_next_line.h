/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:35:56 by gyvergni          #+#    #+#             */
/*   Updated: 2023/12/14 14:35:57 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	end_line(char *str);
char	*clean(char *str);
char	*ft_strdup(const char *str);
char	*append_stock(char *buffer, char *stock);
char	*ft_strstr(char *str, size_t start, size_t end);
char	*get_next_line(int fd);
char	*sub_line(char *stock);
size_t	ft_strlen(const char *str);
#endif
