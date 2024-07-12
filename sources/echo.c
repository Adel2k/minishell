#include "minishell.h"

void	ft_putstr_fd(char *s)
{
	if (s)
	{
		printf("%s\n", s);
		write (1, s, ft_strlen(s));
	}
}

void	echo(char	*str)
{

	ft_putstr_fd(str);
}

void	builtin(t_token *tokens)
{
	if (ft_strcmp(tokens->str, "echov") == 0)
		echo(tokens->str);
}
