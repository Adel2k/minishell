#include "minishell.h"

void	set_pwd(t_minishell *minishell, char *s)
{
	char	*home;

	if (ft_strcmp(minishell->envm->key, "PWD") == 0)
	{
		home = minishell->envm->value;
		minishell->envm->value = ft_strdup(s);
	}
	if (ft_strcmp(minishell->envm->key, "OLDPWD") == 0)
		minishell->envm->value = ft_strdup(home);
}

void	cd_absolute(t_minishell *minishell)
{
	char	*s;

	if (ft_strcmp(minishell->envm->key, "PWD") == 0)
		s = minishell->envm->value;
	if (chdir(minishell->cmd[1]))
	{
		set_pwd(minishell, s);
		return ;
	}
	
}

// void	cd_tilda(t_minishell *minishell, char *path)
// {
	
// }

void	cd_home(t_minishell *minishell)
{
	t_env	*start;
	char	*s;

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
				set_pwd(minishell, s);
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
	// if (minishell->cmd[2][0] == "~")
	// 	cd_tilda(minishell, minishell->cmd[2][0]);
	if (minishell->cmd[1])
		cd_absolute(minishell);
}