/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:03:17 by jaemyu            #+#    #+#             */
/*   Updated: 2025/10/27 20:03:17 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_delay(t_philo *philo, long duration)
{
	long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->rule->d_m);
		if (philo->rule->die_sign)
		{
			pthread_mutex_unlock(&philo->rule->d_m);
			break ;
		}
		pthread_mutex_unlock(&philo->rule->d_m);
		if (get_time() - start >= duration)
			break ;
		usleep(100);
	}
}

int	sign_check(t_philo *philo)
{
	int		i;
	int		sign;

	i = -1;
	sign = 0;
	if (philo->rule->must_eat)
	{
		while (++i < philo->rule->num_of_head)
		{
			pthread_mutex_lock(&philo[i].l_t);
			if (philo[i].meal_cnt >= philo->rule->must_eat)
				sign += 1;
			pthread_mutex_unlock(&philo[i].l_t);
		}
		if (sign == philo->rule->num_of_head)
			return (0);
	}
	return (1);
}

static	int	die_check(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->rule->num_of_head)
	{
		if (!sign_check(philo))
			return (0);
		pthread_mutex_lock(&philo[i].l_t);
		if (get_time() - philo[i].last_eat >= philo->rule->time_to_die)
		{
			pthread_mutex_unlock(&philo[i].l_t);
			pthread_mutex_lock(&philo->rule->d_m);
			if (philo->rule->die_sign == 0)
			{
				print_die(philo, i);
				pthread_mutex_unlock(&philo->rule->d_m);
				return (0);
			}
			pthread_mutex_unlock(&philo->rule->d_m);
		}
		else
			pthread_mutex_unlock(&philo[i].l_t);
	}
	return (1);
}

int	thread_run(t_philo *philo)
{
	int		i;
	int		sign;

	i = -1;
	sign = 0;
	philo->time = get_time();
	while (++i < philo->rule->num_of_head)
		pthread_create(&(philo[i].thread), NULL, routine, philo + i);
	i = -1;
	while (1)
	{
		if (!die_check(philo))
			break ;
		pthread_mutex_lock(&philo->rule->d_m);
		if (philo->rule->die_sign == 1)
		{
			pthread_mutex_unlock(&philo->rule->d_m);
			break ;
		}
		pthread_mutex_unlock(&philo->rule->d_m);
	}
	while (++i < philo->rule->num_of_head)
		pthread_join(philo[i].thread, NULL);
	return (0);
}
