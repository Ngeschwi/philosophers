/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:59:14 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/02 11:43:07 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_spleep;
	int	nbr_time_philo_eat;
}				t_philo;

# define ERROR 1
# define SUCCES 0

int	ft_atoi(const char *str);

#endif