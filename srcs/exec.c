/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:09:57 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:12:23 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo)
{
	if ((timestamp() - philo->last_meal) >= (unsigned long)philo->data->die)
	{
		philo_kill(philo);
		pthread_mutex_unlock(philo->data->forks);
		return (1);
	}
	return (0);
}

static void	supervisor(t_philo *philo, int full, int i)
{
	while (1)
	{
		i = -1;
		full = 0;
		while (++i < philo->data->nb_philo)
		{
			pthread_mutex_lock(philo[i].data->forks);
			if (philo[i].laps_done == philo[i].laps)
			{
				++full;
				if (full == philo->data->nb_philo)
				{
					if (philo_dead(&philo[i]))
						return ;
					pthread_mutex_unlock(philo[i].data->forks);
					return ;
				}
			}
			if (philo_dead(&philo[i]))
				return ;
			pthread_mutex_unlock(philo[i].data->forks);
		}
		usleep(200);
	}
}

int	get_status(t_philo	*philo)
{
	pthread_mutex_lock(philo->data->forks);
	if (philo->data->status != ALIVE)
	{
		pthread_mutex_unlock(philo->data->forks);
		return (DEAD);
	}
	pthread_mutex_unlock(philo->data->forks);
	return (ALIVE);
}

void	*act(void	*philo_data)
{
	t_philo	*philo;

	philo = philo_data;
	while (get_status(philo) == ALIVE)
	{		
		if (philo->laps_done == philo->laps)
			return (NULL);
		eating(philo);
		if (get_status(philo) != ALIVE || philo->laps_done == philo->laps)
			return (NULL);
		sleeping(philo);
		if (get_status(philo) != ALIVE)
			return (NULL);
		thinking(philo);
		if (get_status(philo) != ALIVE)
			return (NULL);
		usleep(200);
	}
	return (NULL);
}

void	execute_philo(t_philo *philo)
{
	int	i;

	i = -1;
	philo->data->time_start = timestamp();
	if (init_mutex(philo) == false)
		return ;
	if (philo->data->nb_philo == 1)
		return (one_philo(philo));
	while (++i < philo->data->nb_philo)
	{
		if (i % 2 == 0)
			if ((pthread_create(&(philo[i].philo_id), NULL, act, &philo[i])))
				return ;
	}
	ft_usleep(10, philo);
	i = -1;
	while (++i < philo->data->nb_philo)
	{
		if (i % 2 == 1)
			if ((pthread_create(&(philo[i].philo_id), NULL, act, &philo[i])))
				return ;
	}
	supervisor(philo, 0xdeadbeef, 0xbabefeed);
}
