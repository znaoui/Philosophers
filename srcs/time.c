/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:24:14 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:24:44 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long unsigned int time_in_ms, t_philo *philo)
{
	long unsigned int	start_time;

	start_time = 0;
	start_time = timestamp();
	while ((timestamp() - start_time) < time_in_ms
		&& get_status(philo) == ALIVE)
		usleep(50);
}

long unsigned int	timestamp(void)
{
	static long					start_time = 0;
	long unsigned int			actual_time;
	struct timeval				tv;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		actual_time = 0;
	}
	else
	{
		gettimeofday(&tv, NULL);
		actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time;
	}
	return (actual_time);
}
