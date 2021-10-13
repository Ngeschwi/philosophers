/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:36:19 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 01:09:15 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print(t_philo *philo, char *str)
{
	unsigned long long	time;


	pthread_mutex_lock(&(philo->data)->mut_print);
	if (gettimeofday(&(philo)->tv_p, NULL) == -1)
		printf("ERROR\n");
	time = philo->tv_p.tv_usec - philo->data->time_start;
	dprintf(1, "%llu Philo %d is %s\n", time, philo->position, str);
	pthread_mutex_unlock(&(philo->data)->mut_print);
}
