/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:07:56 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:09:37 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->data->sleep, philo);
}

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

int	eating(t_philo *philo)
{
	if (philo_take_fork(philo) == 1)
		return (1);
	ft_print(philo, "is eating");
	pthread_mutex_lock(philo->data->forks);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->data->forks);
	ft_usleep(philo->data->eat, philo);
	pthread_mutex_lock(philo->data->forks);
	philo->laps_done++;
	pthread_mutex_unlock(philo->data->forks);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (0);
}

int	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork))
		{
			pthread_mutex_unlock(&philo->right_fork);
			return (1);
		}
		ft_print(philo, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(&philo->right_fork))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		ft_print(philo, "has taken a fork");
	}
	return (0);
}

void	philo_kill(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	printf("%lu philo %d died\n", timestamp(), philo->id + 1);
	philo->data->status = DEAD;
	pthread_mutex_unlock(&philo->lock);
}
