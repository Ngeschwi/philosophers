/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:01:09 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/14 01:09:12 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_philo(t_data *data)
{
	int				i;
	t_philo			philo;
	struct timeval	tv;

	i = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (ERROR);
	data->time_start = tv.tv_usec;
	printf("start : %llu\n", data->time_start);
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		memcpy(&(data->philos[i]), &philo, sizeof(t_philo));
		data->philos[i].position = i;
		data->philos[i].is_eating = 0;
		data->philos[i].eat_count = 0;
		pthread_mutex_init(&(data->philos[i]).mut_fork, NULL);
		if (pthread_create(&(data->philos[i]).pt_philo, NULL, ft_life,
				(void*)&(data)->philos[i]))
			return (ft_error(data, "Error"));
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philos[i].pt_philo, NULL);
		i++;
	}
	return (SUCCES);
}

static int	ft_verif_struct(t_data *data)
{
	if (data->nbr_philo < 0 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_spleep < 60)
	{
		printf("ERROR\nErreur d'arguments\n");
		return (ERROR);
	}
	if (data->nbr_philo > 200)
	{
		printf("ERROR\nLe nombre de philo ne peut pas depasser 200\n");
		return (ERROR);
	}
	else
		return (SUCCES);
}

static int	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_spleep = ft_atoi(argv[4]);
	data->die = 0;
	if (argc == 6)
		data->nbr_time_philo_eat = ft_atoi(argv[5]);
	else
		data->nbr_time_philo_eat = -1;
	if (argc == 6 && data->nbr_time_philo_eat <= 0)
	{
		printf("ERROR\nLe nombre de repas ne peut pas etre nul ou negatif\n");
		return (ERROR);
	}
	if (ft_verif_struct(data) == ERROR)
		return (ERROR);
	pthread_mutex_init(&(data)->mut_print, NULL);
	pthread_mutex_init(&(data)->mut_die, NULL);
	return (SUCCES);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		ft_init_struct(&data, argc, argv);
		ft_init_philo(&data);
	}
	else
	{
		printf("ERROR\nErreur dans le nombre d'arguments\n");
		return (ERROR);
	}
	return (SUCCES);
}
