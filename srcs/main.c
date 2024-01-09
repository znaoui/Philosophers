/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaktarus <znaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:20:45 by zaktarus          #+#    #+#             */
/*   Updated: 2023/01/10 11:31:55 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_run(t_philo *philo)
{
	int	i;

	i = 0;
	if (!philo)
		return ;
	execute_philo(philo);
	if (philo->data->nb_philo == 1)
	{
		free(philo);
		return ;
	}
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo[i].philo_id, NULL);
		i++;
	}
	destroy_mutex(philo);
	if (philo)
		free(philo);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_data	*data;

	if (ft_check_argv(argv) == false)
		return (ft_error("Error: wrong arguments!\n"), 1);
	argc--;
	argv++;
	if (argc < 4 || (argc > 4 && ft_atoi(argv[4]) < 0)
		|| ft_check_args(argv) == false)
		return (ft_error("Error: wrong arguments!\n"), 1);
	if (ft_atoi(argv[0]) == 0 || ft_atoi(argv[0]) == -0
		|| ft_atoi(argv[0]) == +0)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc == 4)
		philo = initialisation(argv, &data);
	else if (argc == 5 && ft_atoi(argv[4]) > 0 && ft_isnum(argv[4]))
		philo = initialisation_loop(argv, &data);
	else
		return (free(data), ft_error("Error: wrong arguments\n"), 1);
	ft_run(philo);
	free(data);
	return (0);
}
