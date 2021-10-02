/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:01:09 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/02 11:43:03 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_verif_struct(t_philo *philo)
{
	if (philo->nbr_philo < 0 || philo->time_to_die < 0 ||
		philo->time_to_eat < 0 || philo->time_to_spleep < 0 ||
		philo->nbr_time_philo_eat < 0)
	{
		printf("Les differents parametres ne peuvents pas etre negatifs");
		return (ERROR);
	}
	else
		return (SUCCES);
}

static int	ft_init_struct(t_philo *philo, int argc, char **argv)
{
	philo->nbr_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_spleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nbr_time_philo_eat = ft_atoi(argv[5]);
	else
		philo->nbr_time_philo_eat = -1;
	if (ft_verif_struct(philo) == ERROR)
		return (ERROR);
	return (SUCCES);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	if (argc == 5 || argc == 6)
	{
		ft_init_struct(&philo, argc, argv);
	}
	else
	{
		printf("Erreur dans le nombre d'arguments");
		return (ERROR);
	}
	return (SUCCES);
}
