#include "minishell.h"

void	ft_putstr_fd(char *s)
{
	if (s)
		write (1, s, ft_strlen(s));
}

void	echo(char **str)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	while (str[i])
	{
		j = 0;
		printf("i = %d,    j = %d\n",i , j);
		if (str[i][j] == '-')
		{
			j++;
			while (str[i][j] == 'n' && (str[i][j + 1] == 'n' || str[i][j + 1] == ' ' || str[i][j + 1] == 0))
			{
				if (str[i][j] != 'n')
					break ;
				j++;
				flag = 1;
			}
			i++;
		}
		ft_putstr_fd(str[i]);
		if (i != matrix_len(str))
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	builtin(t_minishell *minishell)
{
	char **command;

	command = cmd_args(minishell);
	if (ft_strcmp(minishell->tokens->str, "echo") == 0)
		echo(command);
}
