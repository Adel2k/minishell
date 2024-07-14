#include "minishell.h"

void	cd(t_minishell *minishell)
{
	char *s;
	t_env	*start;
	int i;

	i = -1;
	start = minishell->envm;
	while (minishell->env[++i])
	{
		if (ft_strcmp(minishell->envm->key, "HOME") == 0)
		{
			s = minishell->envm->value;
			chdir (minishell->envm->value);
			minishell->envm = start;
			while (minishell->envm)
			{
				if (ft_strcmp(minishell->envm->key, "PWD") == 0)
					minishell->envm->value = s;	
				minishell->envm = minishell->envm->next;
			}
			break ;
		}
		minishell->envm = minishell->envm->next;
	}
}
