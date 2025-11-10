/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:01:27 by jaemyu            #+#    #+#             */
/*   Updated: 2025/10/27 20:01:27 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ph_delay(philo, philo->rule->time_to_sleep);
	print_state(philo, "is thinking");
	usleep(300);
}

void	eat(t_philo *philo, int sign)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->l_t);
	philo->last_eat = now;
	philo->meal_cnt += 1;
	pthread_mutex_unlock(&philo->l_t);
	print_state(philo, "is eating");
	ph_delay(philo, philo->rule->time_to_eat);
	if (sign == 0)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
}

void	right_left(t_philo *philo, int sign)
{
	if (sign == 0)
	{
		pthread_mutex_lock(philo->right);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		print_state(philo, "has taken a fork");
	}
}

static void	dining_etiquette(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rule->d_m);
	if (philo->num % 2 == 0)
		right_left(philo, 0);
	else
		right_left(philo, 1);
	if (philo->num % 2 == 0)
		eat(philo, 0);
	else
		eat(philo, 1);
	sleep_think(philo);
}

void	*routine(void *argv)
{
	t_philo		*philo;

	philo = argv;
	pthread_mutex_lock(&philo->l_t);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->l_t);
	if (philo->rule->num_of_head == 1)
	{
		print_state(philo, "has taken a fork");
		ph_delay(philo, philo->rule->time_to_die);
		return (NULL);
	}
	if (philo->num % 2 == 0)
		ph_delay(philo, philo->rule->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->rule->d_m);
		if (philo->rule->must_eat && philo->rule->must_eat <= philo->meal_cnt)
			return (pthread_mutex_unlock(&philo->rule->d_m), NULL);
		if (philo->rule->die_sign)
			return (pthread_mutex_unlock(&philo->rule->d_m), NULL);
		dining_etiquette(philo);
	}
	return (NULL);
}
