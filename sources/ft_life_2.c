/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:47:11 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/15 16:05:58 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mut_die));
	if (philo->data->die == 1)
	{
		pthread_mutex_unlock(&(philo->data->mut_die));
		return (ERROR);
	}
	pthread_mutex_unlock(&(philo->data->mut_die));
	return (SUCCESS);
}

void	*ft_think(t_philo *philo)
{
	if (ft_check_dead(philo) == SUCCESS)
	{
		gettimeofday(&(philo->tv_p), NULL);
		if ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->time_when_eat > philo->data->time_to_die)
			return (ft_dead(philo));
		else
			ft_print(philo, "thinking");
	}
	else
		return (DEAD);
	return (NOT_DEAD);
}

void	*ft_sleep(t_philo *philo)
{
	if (ft_check_dead(philo) == SUCCESS)
	{
		gettimeofday(&(philo->tv_p), NULL);
		if ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->time_when_eat > philo->data->time_to_die)
			return (ft_dead(philo));
		else
		{
			ft_print(philo, "sleeping");
			usleep(philo->data->time_to_sleep * 1000);
			if (ft_think(philo) == DEAD)
				return (DEAD);
		}
	}
	else
		return (DEAD);
	return (NOT_DEAD);
}

void	*ft_dead(t_philo *philo)
{
	ft_print(philo, "dead");
	pthread_mutex_lock(&(philo->data->mut_die));
	philo->data->die = 1;
	pthread_mutex_unlock(&(philo->data->mut_die));
	return (DEAD);
}

void	*ft_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philos[i].pt_philo, DEAD);
		i++;
	}
	free(data->philos);
	return (DEAD);
}
