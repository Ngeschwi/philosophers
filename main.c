/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:01:09 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/26 00:09:50 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_calcul_posi_fork(t_philo *philo)
{
	int	posi_fork;

	if (philo->position % 2 == 0)
	{
		if (philo->position == philo->data->nbr_philo - 1)
			posi_fork = 0;
		else
			posi_fork = philo->position + 1;
	}
	else
		posi_fork = philo->position - 1;
	return (posi_fork);
}

static int	ft_init_philo(t_data *data)
{
	int				i;
	t_philo			philo;
	struct timeval	tv;

	i = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (ERROR);
	data->time_start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		ft_memcpy(&(data->philos[i]), &philo, sizeof(t_philo));
		data->philos[i].position = i;
		data->philos[i].eat_count = 0;
		data->philos[i].time_when_eat = 0;
		data->philos[i].die_p = 0;
		data->philos[i].posi_fork = ft_calcul_posi_fork(&data->philos[i]);
		pthread_mutex_init(&(data->philos[i].mut_fork), NULL);
		if (pthread_create(&(data->philos[i].pt_philo), NULL, ft_life,
				(void*)&(data)->philos[i]))
			return (ft_error("pthread_creat"));
		pthread_detach(data->philos[i].pt_philo);
		i++;
	}
	return ((int)ft_end(data));
}

static int	ft_verif_struct(t_data *data)
{
	if (data->nbr_philo < 0 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (ft_error("argument error"));
	if (data->nbr_philo > 200)
		return (ft_error("The number of philo cannot exceed 200"));
	else
		return (SUCCESS);
}

static int	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->die = 0;
	data->nbr_die = 0;
	data->print_die = 0;
	if (argc == 6)
		data->nbr_time_philo_eat = ft_atoi(argv[5]);
	else
		data->nbr_time_philo_eat = -1;
	if (argc == 6 && data->nbr_time_philo_eat <= 0)
		return (ft_error("The number of meals cannot be zero or negative"));
	if (ft_verif_struct(data) == ERROR)
		return (ERROR);
	pthread_mutex_init(&(data->mut_print), NULL);
	pthread_mutex_init(&(data->mut_die), NULL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (ft_init_struct(&data, argc, argv) == ERROR)
			return (ERROR);
		if (ft_init_philo(&data) == ERROR)
			return (ERROR);
	}
	else
		return (ft_error("Error in number of arguments"));
	return (SUCCESS);
}
