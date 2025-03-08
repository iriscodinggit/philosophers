/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:59:53 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:59:55 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	print_log(t_philo *philo, char *msg)
{
	long	current_time;
	long	elapsed;

	get_time_mutex(&current_time);
	elapsed = time_passed(&get_rules()->start_time, &current_time);
	pthread_mutex_lock(&get_rules()->print);
	if (check_death_flag() == false)
		printf("%ld %d %s\n", elapsed, philo->index, msg);
	pthread_mutex_unlock(&get_rules()->print);
}
