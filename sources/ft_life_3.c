/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:13:40 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/19 20:57:04 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check_time_dead(t_philo *philo, unsigned long long time)
{
	if (time - philo->time_when_eat > philo->data->time_to_die)
		return (ft_dead(philo));
	pthread_mutex_lock(&(philo->data->mut_die));
	if (philo->data->die == 1)
	{
		pthread_mutex_unlock(&(philo->data->mut_die));
		return (DEAD);
	}
	if (philo->die_p == 1)
	{
		pthread_mutex_unlock(&(philo->data->mut_die));
		return (ft_dead(philo));
	}
	pthread_mutex_unlock(&(philo->data->mut_die));
	return (NOT_DEAD);
}

void	*ft_check_when_eat(t_philo *philo, unsigned long long time)
{
	if (ft_check_time_dead(philo, time) == DEAD)
	{
		ft_un_lock_mutex(philo, 1, EVEN);
		return (DEAD);
	}
	if (time - philo->data->philos[philo->posi_fork].time_when_eat
		+ philo->data->time_to_eat > philo->data->time_to_die)
	{
		pthread_mutex_lock(&(philo->data->mut_die));
		philo->data->philos[philo->posi_fork].die_p = 1;
		pthread_mutex_unlock(&(philo->data->mut_die));
		ft_un_lock_mutex(philo, 1, EVEN);
		ft_print(philo, "taking a fork", time);
		ft_print(philo, "eating", time);
		return (DEAD);
	}
	return (NOT_DEAD);
}