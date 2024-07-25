/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:03 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 20:57:05 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	exit_alt(t_minishell *minishell)
{
	struct termios	old_tio;
	struct termios	new_tio;

	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	if (ft_strcmp(minishell->cmd[0], "exit") == 0 && !(minishell->cmd[1]))
	{
		minishell->is_builtin = 1;
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	len_error(char *str, unsigned long long nbr)
{
	if (nbr > (unsigned long long)LLONG_MAX)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_status = 255;
		exit (g_exit_status);
	}
}

int	ft_latoi(char *str)
{
	size_t				i;
	unsigned long long	nbr;
	int					sign;

	i = 0;
	nbr = 0;
	sign = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		++i;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr > LLONG_MAX)
			len_error(str, nbr);
		++i;
	}
	if (sign)
		return (-nbr);
	return (nbr);
}

void	built_exit(t_minishell *minishell, int is_in_fork, int print)
{
	if (is_in_fork != 1)
		printf("exit\n");
	if (minishell->cmd[1])
	{
		if (minishell->cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			print = 1;
		}
		else if (is_numeric(minishell->cmd[1]))
			g_exit_status = (ft_latoi(minishell->cmd[1]) % 256);
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(minishell->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_status = 255;
		}
	}
	if (g_exit_status < 0)
		g_exit_status += 256;
	if (print != 1)
		exit(g_exit_status);
}
