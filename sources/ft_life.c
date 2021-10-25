/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:29:31 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/26 00:03:04 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_life_only_one(t_philo *philo)
{
	unsigned long long	time;
	unsigned long long	init_time;

	gettimeofday(&(philo->tv_p), NULL);
	init_time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->data->time_start;
	time = init_time;
	printf("%llu Philo %d is taking a fork\n", time, philo->position);
	while (time - init_time < philo->data->time_to_die)
	{
		gettimeofday(&(philo->tv_p), NULL);
		time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->data->time_start;
		usleep(50);
	}
	return (ft_dead(philo));
}

static void	ft_end_nbr_eat(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mut_die));
		if (philo->data->nbr_die == philo->data->nbr_philo)
		{
			philo->data->die = 1;
			pthread_mutex_unlock(&(philo->data->mut_die));
			return ;
		}
		pthread_mutex_unlock(&(philo->data->mut_die));
	}
}

void	*ft_life(void *philo_arg)
{
	t_philo	*philo;

	philo = philo_arg;
	if (philo->data->nbr_philo == 1)
		return (ft_life_only_one(philo));
	while (1)
	{
		if (philo->eat_count >= philo->data->nbr_time_philo_eat
			&& philo->data->nbr_time_philo_eat != -1)
		{
			pthread_mutex_lock(&(philo->data->mut_die));
			philo->data->nbr_die++;
			pthread_mutex_unlock(&(philo->data->mut_die));
			break ;
		}
		if (ft_eat(philo) == DEAD)
			return (DEAD);
		if (ft_sleep(philo) == DEAD)
			return (DEAD);
		if (ft_think(philo) == DEAD)
			return (DEAD);
	}
	ft_end_nbr_eat(philo);
	return (SUCCESS);
}

void	*ft_end(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&(data->mut_die));
		if (data->die == 1)
		{
			pthread_mutex_unlock(&(data->mut_die));
			break ;
		}
		pthread_mutex_unlock(&(data->mut_die));
	}
	free(data->philos);
	return (DEAD);
}
