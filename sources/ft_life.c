/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:29:31 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/15 16:50:08 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_un_lock_mutex(t_philo *philo, int check, int who)
{
	if (check == 0 && who == EVEN)
	{
		pthread_mutex_lock(&(philo->data->philos[philo->posi_fork].mut_fork));
		pthread_mutex_lock(&(philo->mut_fork));
	}
	else if (who == EVEN)
	{
		pthread_mutex_unlock(&(philo->mut_fork));
		pthread_mutex_unlock(&(philo->data->philos[philo->posi_fork].mut_fork));
	}
	if (check == 0 && who == ODD)
	{
		pthread_mutex_lock(&(philo->mut_fork));
		pthread_mutex_lock(&(philo->data->philos[philo->posi_fork].mut_fork));
	}
	else if (who == ODD)
	{
		pthread_mutex_unlock(&(philo->data->philos[philo->posi_fork].mut_fork));
		pthread_mutex_unlock(&(philo->mut_fork));
	}
}

static int	ft_check_time(t_philo *philo)
{
	if (philo->time_when_eat == (unsigned long long) -1)
	{
		if (philo->data->time_to_eat > philo->data->time_to_die)
			return (ERROR);
		else
			return (SUCCESS);
	}
	else
	{
		gettimeofday(&(philo->tv_p), NULL);
		if ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->time_when_eat > philo->data->time_to_die)
			return (ERROR);
		else
			return (SUCCESS);
	}
}

void	*ft_eat(t_philo *philo)
{
	if (ft_check_dead(philo) == SUCCESS)
	{
		if (philo->position % 2 == 0)
			ft_un_lock_mutex(philo, 0, EVEN);
		else
			ft_un_lock_mutex(philo, 0, ODD);
		if (ft_check_time(philo) == ERROR)
			return (ft_dead(philo));
		ft_print(philo, "taking a fork");
		ft_print(philo, "eating");
		philo->eat_count++;
		usleep(philo->data->time_to_eat * 1000);
		if (philo->position % 2 == 0)
			ft_un_lock_mutex(philo, 1, EVEN);
		else
			ft_un_lock_mutex(philo, 1, ODD);
		if (ft_sleep(philo) == DEAD)
			return (DEAD);	
	}
	else
		return (DEAD);
	return (NOT_DEAD);
}

void	*ft_life(void *philo_arg)
{
	t_philo	*philo;

	philo = philo_arg;
	if (philo->data->nbr_time_philo_eat != -1)
	{
		while (philo->eat_count < philo->data->nbr_time_philo_eat)
		{
			if (ft_eat(philo) == DEAD)
				return (DEAD);
		}
	}
	else
	{
		while (1)
		{
			if (ft_eat(philo) == DEAD)
				return (DEAD);
		}
	}
	pthread_mutex_lock(&(philo->data->mut_die));
	philo->data->die = 1;
	pthread_mutex_unlock(&(philo->data->mut_die));
	return (SUCCESS);
}
