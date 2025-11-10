/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:31:17 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/07 16:09:45 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_tool	tool;
	t_philo	*philo;

	philo = NULL;
	if (!(ac >= 5 && ac <= 6))
		return (1);
	if (init(av, &tool) || philo_alloc(&philo, &tool) \
		|| mutex_init(philo, &tool))
		return (1);
	pthread_mutex_init(&(tool.p_m), NULL);
	pthread_mutex_init(&(tool.d_m), NULL);
	thread_run(philo);
	demise(philo);
	return (0);
}
