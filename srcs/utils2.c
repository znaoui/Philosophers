/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:19:12 by znaoui            #+#    #+#             */
/*   Updated: 2023/01/10 11:24:03 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		ft_print(philo, "has taken a fork");
		ft_usleep(philo->data->die, philo);
		philo_kill(philo);
		destroy_mutex(philo);
	}
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	diff;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			return (diff);
		}
		i++;
	}
	return (0);
}

int	ft_check_args(char **argv)
{
	int	i;

	i = 0;
	if (ft_strcmp(argv[0], "-0") == 0)
		i++;
	while (argv[i] != NULL)
	{
		if (ft_isnum(argv[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

int	ft_check_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) >= 12)
			return (false);
		if (ft_strcmp(argv[i], "") == 0)
			return (false);
		i++;
	}
	return (true);
}
