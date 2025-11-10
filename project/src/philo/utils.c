/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:42:35 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/09 15:38:38 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	demise(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->rule->num_of_head)
		pthread_mutex_destroy(philo[i].right);
	pthread_mutex_destroy(&philo->rule->p_m);
	pthread_mutex_destroy(&philo->rule->d_m);
	pthread_mutex_destroy(&philo->l_t);
	free(philo->right);
	free(philo);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ph_atoi(const char *nptr)
{
	long	value;
	int		digit;

	value = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (value > (2147483647 - digit) / 10)
			return (0);
		value = value * 10 + digit;
		nptr++;
	}
	return ((int)value);
}
