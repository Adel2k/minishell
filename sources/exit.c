/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:03 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 13:43:28 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_alt(t_minishell *minishell)
{
	struct termios	old_tio;
	struct termios	new_tio;

	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	if (ft_strcmp(minishell->cmd[0], "exit") == 0 && !(minishell->cmd[1]))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
	// if (minishell->cmd[1])
	// {
	// 	write(STDOUT_FILENO, "exit\n", 5);
	// 	err_message("minishell: ", "exit:", " too many arguments\n");
	// }
}
