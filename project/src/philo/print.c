/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:00:26 by jaemyu            #+#    #+#             */
/*   Updated: 2025/10/27 20:00:26 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_die(t_philo *philo, int num)
{
	long	timestamp;

	timestamp = get_time() - philo->rule->start_time;
	philo->rule->die_sign = 1;
	pthread_mutex_lock(&philo->rule->p_m);
	printf("%ld %d died\n", timestamp, num + 1);
	pthread_mutex_unlock(&philo->rule->p_m);
}

void	print_state(t_philo *philo, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rule->d_m);
	if (!philo->rule->die_sign)
	{
		pthread_mutex_unlock(&philo->rule->d_m);
		timestamp = get_time() - philo->rule->start_time;
		pthread_mutex_lock(&philo->rule->p_m);
		printf("%ld %d %s\n", timestamp, philo->num + 1, msg);
		pthread_mutex_unlock(&philo->rule->p_m);
	}
	else
		pthread_mutex_unlock(&philo->rule->d_m);
}
