/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:29:31 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/19 20:23:49 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_life_only_one(t_philo *philo)
{
	unsigned long long	time;

	gettimeofday(&(philo->tv_p), NULL);
	time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->data->time_start;
	ft_print(philo, "taking a fork", time);
	usleep(philo->data->time_to_die * 1000);
	return (ft_dead(philo));
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
			return (SUCCESS);
		if (ft_eat(philo) == DEAD)
			return (DEAD);
		if (ft_sleep(philo) == DEAD)
			return (DEAD);
		if (ft_think(philo) == DEAD)
			return (DEAD);
	}
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
