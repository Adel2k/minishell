#include "minishell.h"

int	matrix_len(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s)
{
	if (s)
		write (1, s, ft_strlen(s));
}