/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujemin <yujemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:00:39 by yujemin           #+#    #+#             */
/*   Updated: 2025/09/12 23:59:51 by yujemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void     init(char **av, t_tool *tool)
{
    tool->surv = ph_atoi(av[1]);
    tool->eat_time = ph_atoi(av[2]);
    tool->sleep_time = ph_atoi(av[3]);
    if (av[4])
        tool->eat_number = ph_atoi(av[4]);
}

int main(int ac, char **av)
{
    t_tool      tool;

    //av[1] == 생존시간
    //av[2] == 먹는시간
    //av[3] == 자는시간
    //av[4](선택적 인자) == 식사 횟수(지정 안하면 철학자 한명 뒤질때 프로그램 꺼짐)
    if (ac < 4 || ac > 5)
        return (1);
    else
        init(av, &tool);
}