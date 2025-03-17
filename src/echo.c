/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:46:44 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/17 01:59:03 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(char	**input)
{
	int	i;
	int	nl;

	i = 0;
	while (ft_str_equals(input[i], "-n"))
		i++;
	nl = i;
	while (input[i])
	{
		printf("%s", input[i]);
		i++;
		if (input[i])
			printf(" ");
	}
	if (!nl)
		printf("\n");
}
