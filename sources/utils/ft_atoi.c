/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:13:04 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/25 23:25:23 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	total;
	int					nbrless;

	nbrless = 1;
	i = 0;
	total = 0;
	if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	if (total > MAX_INT)
		return (0);
	if (str[i] != '\0')
		return (0);
	return (total * nbrless);
}
