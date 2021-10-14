/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:59:14 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 20:05:14 by ngeschwi         ###   ########.fr       */
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
	int					position;
	int					eat_count;
	unsigned long long	time_when_eat;
	int					posi_fork;
	struct timeval		tv_p;
	pthread_t			pt_philo;
	pthread_mutex_t		mut_fork;
	struct s_data		*data;
}				t_philo;

typedef struct s_data
{
	int					nbr_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					nbr_time_philo_eat;
	unsigned long long	time_start;
	int					die;
	t_philo				*philos;
	pthread_mutex_t		mut_print;
	pthread_mutex_t		mut_die;
}				t_data;

# define ERROR 1
# define SUCCESS 0
# define EVEN 1
# define ODD 0

void	*ft_life(void *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_dead(t_philo *philo);
void	*ft_end(t_data *data);
void	ft_print(t_philo *philo, char *str);
int		ft_error(char *str);

int		ft_atoi(const char *str);

#endif