/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:56:27 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/11 13:56:29 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	length(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static long	ft_sign(long n)
{
	int	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static char	*str_new(size_t n)
{
	char	*memory;

	memory = (char *)malloc(n + 1);
	if (!memory)
		return (NULL);
	return (memory);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	nb;
	int				flag;
	char			*result;

	flag = 0;
	if (n < 0)
		flag = 1;
	len = length(n);
	result = str_new(len);
	if (!result)
		return (NULL);
	*(result + len) = 0;
	nb = ft_sign(n);
	while (len--)
	{
		*(result + len) = '0' + nb % 10;
		nb /= 10;
	}
	if (flag)
		*(result) = 45;
	return (result);
}
