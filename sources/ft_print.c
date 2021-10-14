/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:36:19 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 19:43:02 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	unsigned long long	time;

	pthread_mutex_lock(&(philo->data->mut_print));
	gettimeofday(&(philo->tv_p), NULL);
	time = ((philo->tv_p.tv_sec * 1000) + (philo->tv_p.tv_usec / 1000))
		- philo->data->time_start;
	if (str[0] == 'e')
		philo->time_when_eat = (philo->tv_p.tv_sec * 1000)
			+ (philo->tv_p.tv_usec / 1000);
	dprintf(1, "%llu Philo %d is %s\n", time, philo->position, str);
	pthread_mutex_unlock(&(philo->data->mut_print));
}
