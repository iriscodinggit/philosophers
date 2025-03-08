/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:00:26 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 18:00:27 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	stop_simulation(int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		pthread_join(get_rules()->philo[i].id, NULL);
		i++;
	}
	i = 0;
	while (i < philo_nb)
	{
		pthread_mutex_destroy(&get_rules()->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&get_rules()->print);
	pthread_mutex_destroy(&get_rules()->death);
	pthread_mutex_destroy(&get_rules()->meals);
	pthread_mutex_destroy(&get_rules()->time);
	pthread_mutex_destroy(&get_rules()->all_ate_mutex);
	free(get_rules()->forks);
	free(get_rules()->philo);
}
