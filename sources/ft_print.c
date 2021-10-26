/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:36:19 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/26 17:29:22 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str, unsigned long long time)
{
	pthread_mutex_lock(&(philo->data->mut_print));
	if (philo->data->print_die == 0)
	{
		pthread_mutex_unlock(&(philo->data->mut_print));
		printf("%llu Philo %d is %s\n", time, philo->position, str);
		if (str[0] == 't' && str[1] == 'a')
		{
			philo->time_when_eat = time;
			printf("%llu Philo %d is eating\n", time, philo->position);
		}
	}
	pthread_mutex_unlock(&(philo->data->mut_print));
}

void	ft_print_dead(t_philo *philo, unsigned long long time)
{
	pthread_mutex_lock(&(philo->data->mut_print));
	if (philo->data->print_die == 0)
	{
		philo->data->print_die = 1;
		pthread_mutex_unlock(&(philo->data->mut_print));
		printf("%llu Philo %d is dead\n", time, philo->position);
	}
	pthread_mutex_unlock(&(philo->data->mut_print));
}
