/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:09:31 by jaemyu            #+#    #+#             */
/*   Updated: 2025/09/16 00:09:31 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_tool
{
	int				num_of_head;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				die_sign;
	long			start_time;
	pthread_mutex_t	p_m;
	pthread_mutex_t	d_m;
}	t_tool;

typedef struct s_philo
{
	int				num;
	int				meal_cnt;
	long			time;
	long			last_eat;
	t_tool			*rule;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	l_t;
}	t_philo;

int		init(char **path, t_tool *tool);
int		philo_alloc(t_philo **philo, t_tool *tool);
void	philo_init(t_philo *philo, pthread_mutex_t *fork, t_tool *tool, int i);
int		mutex_init(t_philo *philo, t_tool *tool);

void	sleep_think(t_philo *philo);
void	right_left(t_philo *philo, int sign);
void	*routine(void *argv);

void	ph_delay(t_philo *philo, long duration);
int		sign_check(t_philo *philo);
int		thread_run(t_philo *philo);

void	print_die(t_philo *philo, int num);
void	print_state(t_philo *philo, const char *msg);

int		ph_atoi(const char *nptr);
void	demise(t_philo *philo);
long	get_time(void);

#endif