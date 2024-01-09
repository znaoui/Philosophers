/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:32:11 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:32:13 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[0]);
	data->die = ft_atoi(argv[1]);
	data->eat = ft_atoi(argv[2]);
	data->sleep = ft_atoi(argv[3]);
	data->status = ALIVE;
	data->time_finish = 0;
}

t_philo	*initialisation(char **argv, t_data **data)
{
	t_philo		*philo;
	static int	i = -1;

	ft_init_data(*data, argv);
	philo = malloc(sizeof(t_philo) * (ft_atoi(argv[0])));
	if (!philo)
		return (0);
	while (++i < ft_atoi(argv[0]))
	{
		philo[i].data = *data;
		philo[i].id = i;
		philo[i].laps = -1;
		philo[i].laps_done = 0;
		philo[i].last_meal = 0;
		philo[i].status = ALIVE;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		philo[(i + 1) % philo->data->nb_philo].left_fork
			= &philo[i].right_fork;
	}
	return (philo);
}

t_philo	*initialisation_loop(char **argv, t_data **data)
{
	t_philo		*philo;
	static int	i = -1;

	ft_init_data(*data, argv);
	philo = malloc(sizeof(t_philo) * (ft_atoi(argv[0])));
	if (!philo)
		return (0);
	while (++i < ft_atoi(argv[0]))
	{
		philo[i].data = *data;
		philo[i].id = i;
		philo[i].laps_done = 0;
		philo[i].last_meal = 0;
		philo[i].laps = ft_atoi(argv[4]);
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&philo[i].right_fork, NULL);
		philo[(i + 1) % philo->data->nb_philo].left_fork
			= &philo[i].right_fork;
		philo[i].status = ALIVE;
	}
	return (philo);
}

int	init_mutex(t_philo *test)
{
	test->data->forks = malloc(sizeof(t_mutex));
	if (!test->data->forks)
		return (false);
	test->data->lock = malloc(sizeof(t_mutex));
	if (!test->data->lock)
		return (false);
	pthread_mutex_init(test->data->forks, NULL);
	pthread_mutex_init(test->data->lock, NULL);
	return (true);
}

void	destroy_mutex(t_philo	*test)
{
	free(test->data->forks);
	free(test->data->lock);
}
