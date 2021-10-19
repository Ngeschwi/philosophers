/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:36:19 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/19 20:46:45 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str, unsigned long long time)
{
	if (str[0] == 'd')
		usleep(10);
	if (str[0] == 'e')
		philo->time_when_eat = time;
	pthread_mutex_lock(&(philo->data->mut_print));
	dprintf(1, "%llu Philo %d is %s\n", time, philo->position, str);
	pthread_mutex_unlock(&(philo->data->mut_print));
}

void	ft_print_dead(t_philo *philo, unsigned long long time)
{
	usleep(10);
	pthread_mutex_lock(&(philo->data->mut_print));
	dprintf(1, "%llu Philo %d is dead\n", time, philo->position);
	pthread_mutex_unlock(&(philo->data->mut_print));
}
