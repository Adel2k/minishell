/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:56:05 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/11 13:56:06 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_check(void *str)
{
	if (!str)
		error_handle();
}

void	error_handle(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
