/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:47:11 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 19:55:31 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	gettimeofday(&(philo->tv_p), NULL);
	if ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->time_when_eat > philo->data->time_to_die)
		ft_dead(philo);
	else
		ft_print(philo, "thinking");
}

void	ft_sleep(t_philo *philo)
{
	gettimeofday(&(philo->tv_p), NULL);
	if ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->time_when_eat > philo->data->time_to_die)
		ft_dead(philo);
	else
	{
		ft_print(philo, "sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		ft_think(philo);
	}
}

void	ft_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mut_die));
	usleep(50);
	ft_print(philo, "dead");
	philo->data->die = 1;
	pthread_mutex_unlock(&(philo->data->mut_die));
}

void	*ft_end(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&(data->mut_die));
		if (data->die == 1)
		{
			usleep(10);
			return (SUCCESS);
		}
		pthread_mutex_unlock(&(data->mut_die));
	}
}
