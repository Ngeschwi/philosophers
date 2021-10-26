/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:13:40 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/26 16:59:47 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_check_other_dead(t_philo *philo)
{
	int	i;

	i = 0;
	usleep(100);
	while (i < philo->data->nbr_philo)
	{
		if (philo->data->philos[i].die_p == 1)
		{
			pthread_mutex_unlock(&(philo->data->mut_die));
			return (DEAD);
		}
		i++;
	}
	return (NOT_DEAD);
}

void	*ft_check_time_dead(t_philo *philo, unsigned long long time)
{
	if (philo->data->time_to_die < philo->data->time_to_eat)
	{
		ft_print(philo, "taking a fork", time);
		return (ft_dead(philo));
	}
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
	if (ft_check_other_dead(philo) == DEAD)
		return (DEAD);
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
		return (DEAD);
	}
	return (NOT_DEAD);
}
