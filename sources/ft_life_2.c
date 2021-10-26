/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:47:11 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/26 17:41:41 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_un_lock_mutex(t_philo *philo, int check, int who)
{
	if (check == 0 && who == EVEN)
	{
		pthread_mutex_lock(&(philo->data->philos[philo->posi_fork].mut_fork));
		pthread_mutex_lock(&(philo->mut_fork));
	}
	else if (check == 0 && who == ODD)
	{
		pthread_mutex_lock(&(philo->mut_fork));
		pthread_mutex_lock(&(philo->data->philos[philo->posi_fork].mut_fork));
	}
	if (check == 1)
	{
		pthread_mutex_unlock(&(philo->mut_fork));
		pthread_mutex_unlock(&(philo->data->philos[philo->posi_fork].mut_fork));
	}
}

void	*ft_think(t_philo *philo)
{
	unsigned long long	time;

	gettimeofday(&(philo->tv_p), NULL);
	time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->data->time_start;
	if (ft_check_time_dead(philo, time) == DEAD)
		return (DEAD);
	ft_print(philo, "thinking", time);
	return (NOT_DEAD);
}

void	*ft_sleep(t_philo *philo)
{
	unsigned long long	time;
	unsigned long long	init_time;

	gettimeofday(&(philo->tv_p), NULL);
	init_time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->data->time_start;
	time = init_time;
	if (ft_check_time_dead(philo, time) == DEAD)
		return (DEAD);
	ft_print(philo, "sleeping", time);
	while (time - init_time < philo->data->time_to_sleep)
	{
		gettimeofday(&(philo->tv_p), NULL);
		time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->data->time_start;
		usleep(50);
	}
	return (NOT_DEAD);
}

void	*ft_eat(t_philo *philo)
{
	unsigned long long	time;
	unsigned long long	init_time;

	if (philo->position % 2 == 0)
		ft_un_lock_mutex(philo, 0, EVEN);
	else
		ft_un_lock_mutex(philo, 0, ODD);
	gettimeofday(&(philo->tv_p), NULL);
	init_time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
		- philo->data->time_start;
	time = init_time;
	if (ft_check_when_eat(philo, time) == DEAD)
		return (DEAD);
	ft_print(philo, "taking a fork", time);
	philo->eat_count++;
	while (time - init_time < philo->data->time_to_eat)
	{
		gettimeofday(&(philo->tv_p), NULL);
		time = (philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000)
			- philo->data->time_start;
		usleep(50);
	}
	ft_un_lock_mutex(philo, 1, EVEN);
	return (NOT_DEAD);
}

void	*ft_dead(t_philo *philo)
{
	unsigned long long	time;

	usleep(100);
	pthread_mutex_lock(&(philo->data->mut_die));
	time = philo->time_when_eat + philo->data->time_to_die;
	ft_print_dead(philo, time);
	philo->data->die = 1;
	philo->die_p = 1;
	pthread_mutex_unlock(&(philo->data->mut_die));
	return (DEAD);
}
