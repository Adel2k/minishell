#include "minishell.h"

// void	cd_absolute(t_minishell *minishell)
// {

// }

void	cd_home(t_minishell *minishell)
{
	char	*s;
	char	*home;
	t_env	*start;

	start = minishell->envm;
	while (minishell->envm)
	{
		if (ft_strcmp(minishell->envm->key, "HOME") == 0)
		{
			s = minishell->envm->value;
			chdir (minishell->envm->value);
			minishell->envm = start;
			while (minishell->envm)
			{
				if (ft_strcmp(minishell->envm->key, "PWD") == 0)
				{
					home = minishell->envm->value;
					minishell->envm->value = ft_strdup(s);
				}
				if (ft_strcmp(minishell->envm->key, "OLDPWD") == 0)
					minishell->envm->value = ft_strdup(home);
				minishell->envm = minishell->envm->next;
			}
			break ;
		}
		minishell->envm = minishell->envm->next;
	}
	minishell->envm = start;
}

void	cd(t_minishell *minishell)
{
	if (!(minishell->cmd[1]))
		cd_home(minishell);
	// if (minishell->cmd[1])
	// 	cd_absolute(minishell);
}