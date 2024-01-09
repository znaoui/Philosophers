/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaktarus <znaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:21:24 by zaktarus          #+#    #+#             */
/*   Updated: 2023/01/10 11:30:28 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stddef.h>
# include <limits.h>

# define DEAD 0
# define ALIVE 1
# define SLEEPING 2
# define EATING 3

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	long long	time_start;
	int			time_finish;
	int			nb_philo;
	int			nb_meal;
	int			die;
	int			eat;
	int			sleep;
	int			status;
	t_mutex		*forks;
	t_mutex		*lock;
}			t_data;

typedef struct s_philo
{
	pthread_t		philo_id;
	t_data			*data;
	int				id;
	long long int	last_meal;
	int				meal;
	int				laps;
	int				status;
	int				laps_done;
	t_mutex			*left_fork;
	t_mutex			right_fork;
	t_mutex			lock;
	t_mutex			*lock2;
	t_mutex			aff;
}			t_philo;

long unsigned int	timestamp(void);
int					philo_take_fork(t_philo *philo);
int					ft_check_args(char **argv);
int					ft_check_argv(char **argv);
int					get_status(t_philo	*philo);
int					eating(t_philo *philo);
int					ft_atoi(const char *str);
int					init_mutex(t_philo *data);
int					ft_strlen(char *str);
int					ft_isnum(char *str);
void				ft_error(char *str);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				destroy_mutex(t_philo	*data);
void				ft_print(t_philo *philo, const char *msg1);
void				execute_philo(t_philo *philo);
void				philo_kill(t_philo *philo);
void				ft_run(t_philo *philo);
void				one_philo(t_philo *philo);
void				ft_usleep(long unsigned int time_in_ms, t_philo *philo);
t_philo				*initialisation(char **argv, t_data **data);
t_philo				*initialisation_loop(char **argv, t_data **data);

#endif
