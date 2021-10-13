/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:29:31 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 01:11:48 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "sleeping");
	usleep(philo->data->time_to_spleep * 1000);
}

void	ft_eat(t_philo *philo)
{
	int	posi_on_right;

	if (philo->position == philo->data->nbr_philo - 1)
		posi_on_right = 0;
	else
		posi_on_right = philo->position + 1;
	if (philo->position % 2 == 0)
	{
		pthread_mutex_lock(&(philo)->mut_fork);
		pthread_mutex_lock(&(philo->data->philos[posi_on_right]).mut_fork);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->philos[posi_on_right]).mut_fork);
		pthread_mutex_lock(&(philo)->mut_fork);
	}
	ft_print(philo, "eating");
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
	if (philo->position % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->data->philos[posi_on_right]).mut_fork);
		pthread_mutex_unlock(&(philo)->mut_fork);
	}
	else
	{
		pthread_mutex_unlock(&(philo)->mut_fork);
		pthread_mutex_unlock(&(philo->data->philos[posi_on_right]).mut_fork);
	}
}

void	*ft_life(void *philo_arg)
{
	t_philo	*philo;

	philo = philo_arg;
	while (philo->eat_count < philo->data->nbr_time_philo_eat)
	{
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (SUCCES);
}
