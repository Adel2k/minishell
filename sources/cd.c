/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:48:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/25 13:00:00 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		chdir(ft_strjoin_heredoc(home, minishell->cmd[1] + 1));
		set_pwd(minishell, old, getcwd(path2, PATH_MAX));
	}
}

void	cd_error(t_minishell *minishell)
{
	struct stat	info;

	if (stat(minishell->cmd[1], &info) < 0)
	{
		if (!(S_ISDIR(info.st_mode)) && !(S_ISREG(info.st_mode)))
			err_message("minishell: cd: ", minishell->cmd[1],
				": No such file or directory\n");
		else if (!(S_ISDIR(info.st_mode)))
			err_message("minishell: cd: ", minishell->cmd[1],
				": Not a directory\n");
		else if ((S_ISDIR(info.st_mode) || S_ISREG(info.st_mode))
			&& access(minishell->cmd[1], R_OK | X_OK))
			err_message("minishell: cd: ", minishell->cmd[1], ": Permission denied.\n");
	}
	else if (!(S_ISDIR(info.st_mode)))
		err_message("minishell: cd: ", minishell->cmd[1],
			": Not a directory\n");
	else if (access(minishell->cmd[1], R_OK | X_OK)
		&& (S_ISDIR(info.st_mode) || S_ISREG(info.st_mode)))
			err_message("minishell: cd: ", minishell->cmd[1], ": Permission denied.\n");
	else
		cd_absolute(minishell);
}

void	cd(t_minishell *minishell)
{

	if (!(minishell->cmd[1]))
		cd_home(minishell);
	if (minishell->cmd[1] && minishell->cmd[1][0] == '~')
		cd_tilda(minishell);
	else if (minishell->cmd[1])
		cd_error(minishell);
}
