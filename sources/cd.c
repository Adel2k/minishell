/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:48:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 08:48:45 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_minishell *minishell, char *old, char *new)
{
	t_env	*start;

	start = minishell->envm;
	while (minishell->envm)
	{
		if (ft_strcmp(minishell->envm->key, "PWD") == 0)
		{
			free(minishell->envm->value);
			minishell->envm->value = ft_strdup(new);
		}
		if (ft_strcmp(minishell->envm->key, "OLDPWD") == 0)
		{
			free(minishell->envm->value);
			minishell->envm->value = ft_strdup(old);
		}
		minishell->envm = minishell->envm->next;
	}
	minishell->envm = start;
}

void	cd_absolute(t_minishell *minishell)
{
	char	*old;
	char	*new;
	char	path[PATH_MAX];
	char	path2[PATH_MAX];

	old = getcwd(path, PATH_MAX);
	chdir(minishell->cmd[1]);
	new = getcwd(path2, PATH_MAX);
	set_pwd(minishell, old, new);
}

void	cd_home(t_minishell *minishell)
{
	t_env	*start;
	char	*old;
	char	*new;
	char	path[PATH_MAX];
	char	path2[PATH_MAX];

	start = minishell->envm;
	old = getcwd(path, PATH_MAX);
	while (start)
	{
		if (ft_strcmp(start->key, "HOME") == 0)
		{
			chdir (start->value);
			break ;
		}
		start = start->next;
	}
	new = getcwd(path2, PATH_MAX);
	set_pwd(minishell, old, new);
}

void	cd_tilda(t_minishell *minishell)
{
	t_env	*start;
	char	*home;
	char	*old;
	char	path[PATH_MAX];
	char	path2[PATH_MAX];

	start = minishell->envm;
	if (minishell->cmd[1][1] == 0)
		cd_home(minishell);
	else
	{
		old = getcwd(path, PATH_MAX);
		while (minishell->envm)
		{
			if (ft_strcmp(minishell->envm->key, "HOME") == 0)
				home = ft_strdup(minishell->envm->value);
			minishell->envm = minishell->envm->next;
		}
		minishell->envm = start;
		chdir(ft_strjoin(home, minishell->cmd[1] + 1));
		set_pwd(minishell, old, getcwd(path2, PATH_MAX));
	}
}

void	cd(t_minishell *minishell)
{
	struct stat	info;

	if (!(minishell->cmd[1]))
		cd_home(minishell);
	if (minishell->cmd[1] && minishell->cmd[1][0] == '~')
		cd_tilda(minishell);
	else if (minishell->cmd[1])
	{
		if (stat(minishell->cmd[1], &info) < 0)
		{
			if (!(S_ISDIR(info.st_mode)) && !(S_ISREG(info.st_mode)))
				err_message("minishell: ", minishell->cmd[1], " is not a directory or file\n");
			else if ((S_ISDIR(info.st_mode) || S_ISREG(info.st_mode)) && access(minishell->cmd[1], R_OK | X_OK))
				err_message("minishell: ", "", "Permission denied.\n");
			else if (!(S_ISDIR(info.st_mode)))
				err_message("minishell: ", minishell->cmd[1], " is not a directory\n");
		}
		else if (access(minishell->cmd[1], R_OK | X_OK) && (S_ISDIR(info.st_mode) || S_ISREG(info.st_mode)))
			err_message("minishell: ", "", "Permission denied.\n");
		else if (!(S_ISDIR(info.st_mode)))
			err_message("minishell: ", minishell->cmd[1], " is not a directory\n");
		else
			cd_absolute(minishell);
	}
}
