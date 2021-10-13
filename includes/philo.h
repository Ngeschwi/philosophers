/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:59:14 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 01:03:53 by ngeschwi         ###   ########.fr       */
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

struct		s_data;

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				eat_count;
	struct timeval	tv_p;
	pthread_t		pt_philo;
	pthread_mutex_t	mut_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int						nbr_philo;
	unsigned long long		time_to_die;
	unsigned long long		time_to_eat;
	unsigned long long		time_to_spleep;
	int						nbr_time_philo_eat;
	unsigned long long		time_start;
	int						die;
	t_philo					*philos;
	pthread_mutex_t			mut_print;
	pthread_mutex_t			mut_die;
}				t_data;

# define ERROR 1
# define SUCCES 0

void	*ft_life(void *philo);
void	ft_print(t_philo *philo, char *str);
int		ft_error(t_data *data, char *str);

int		ft_atoi(const char *str);

#endif