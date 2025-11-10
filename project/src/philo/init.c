/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:58:31 by jaemyu            #+#    #+#             */
/*   Updated: 2025/10/27 19:58:31 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(char **path, t_tool *tool)
{
	tool->num_of_head = ph_atoi(path[1]);
	tool->time_to_die = ph_atoi(path[2]);
	tool->time_to_eat = ph_atoi(path[3]);
	tool->time_to_sleep = ph_atoi(path[4]);
	tool->start_time = get_time();
	tool->die_sign = 0;
	if ((!tool->num_of_head) || (!tool->time_to_die) || (!tool->time_to_eat) \
	|| (!tool->time_to_sleep))
		return (printf("error: Invalid argument"), 1);
	if (path[5])
	{
		tool->must_eat = ph_atoi(path[5]);
		if (!tool->must_eat)
			return (printf("error: Invalid argument"), 1);
	}
	else
		tool->must_eat = 0;
	return (0);
}

int	philo_alloc(t_philo **philo, t_tool *tool)
{
	pthread_mutex_t	**fork;

	*philo = malloc(sizeof(t_philo) * tool->num_of_head);
	if (!*philo)
		return (1);
	fork = &(*philo)->right;
	*fork = malloc(sizeof(pthread_mutex_t) * tool->num_of_head);
	if (!*fork)
		return (free(*philo), 1);
	return (0);
}

void	philo_init(t_philo *philo, pthread_mutex_t *fork, t_tool *tool, int i)
{
	philo[i].num = i;
	philo[i].rule = tool;
	philo[i].meal_cnt = 0;
	if (i == 0)
	{
		philo[i].right = &fork[i];
		philo[i].left = &fork[tool->num_of_head - 1];
	}
	else
	{
		philo[i].right = &fork[i];
		philo[i].left = &fork[i - 1];
	}
	philo[i].last_eat = tool->start_time;
}

int	mutex_init(t_philo *philo, t_tool *tool)
{
	pthread_mutex_t		*fork;
	int					i;

	i = -1;
	fork = philo->right;
	while (++i < tool->num_of_head)
	{
		philo_init(philo, fork, tool, i);
		if (pthread_mutex_init(&philo[i].l_t, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philo[i].l_t);
			return (free(fork), free(philo), 1);
		}
		if (pthread_mutex_init(fork + i, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork[i]);
			return (free(fork), free(philo), 1);
		}
	}
	return (0);
}
