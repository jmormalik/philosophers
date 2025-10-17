/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujemin <yujemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:46:54 by yujemin           #+#    #+#             */
/*   Updated: 2025/09/12 23:57:37 by yujemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_tool
{
    int     surv;
    int     philp;
    int     eat_time;
    int     sleep_time;
    int     eat_number;
}   t_tool;


int	ph_atoi(const char *nptr);

#endif