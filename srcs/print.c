/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:25:02 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:25:04 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, const char *msg1)
{
	pthread_mutex_lock(philo->data->forks);
	if (philo->data->status == DEAD)
	{
		pthread_mutex_unlock(philo->data->forks);
		return ;
	}
	printf("%lu %d %s\n", timestamp(), philo->id + 1, msg1);
	pthread_mutex_unlock(philo->data->forks);
}
