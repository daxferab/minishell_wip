/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:46:44 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/17 02:10:03 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(char	**input)
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	while (input[i] && ft_str_equals(input[i], "-n"))
	{
		nl = false;
		i++;
	}
	while (input[i])
	{
		printf("%s", input[i]);
		i++;
		if (input[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}
