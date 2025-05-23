/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-olm <pdel-olm@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:15:29 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/04/30 22:01:39 by pdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H
# define EXTRA_H

# include "libft.h"

bool	ft_atoi_better(char *str, int *num);
size_t	ft_count_char(char *s, int c);
char	*ft_dtoa(double n, int decimals);
bool	ft_free_double_pointer(void **double_pointer);
int		ft_get_max(int a, int b);
int		ft_get_min(int a, int b);
bool	ft_str_equals(char *s1, char *s2);

#endif