/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:00:17 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 18:00:19 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

bool	start_simulation(char **argv)
{
	if (parse_fill_rules(argv) == false)
		return (false);
	if (mutex_create() == false)
		return (false);
	allocate_resources(PHILOS);
	get_time_ms(&get_rules()->start_time, 0);
	if (philo_create() == false)
		return (false);
	if (threads_create() == false)
		return (false);
	supervisor();
	stop_simulation(get_rules()->philo_nb);
	return (true);
}

bool	philo_create(void)
{
	int	i;

	i = -1;
	while (++i < get_rules()->philo_nb)
	{
		get_rules()->philo[i].index = i + 1;
		get_rules()->philo[i].time2die = get_rules()->time_to_die;
		get_rules()->philo[i].nb_of_meals = 0;
		if (i + 1 == get_rules()->philo_nb)
		{
			get_rules()->philo[i].left_fork = &get_rules()->forks[(i + 1)
			% get_rules()->philo_nb];
			get_rules()->philo[i].right_fork = &get_rules()->forks[i];
		}
		else
		{
			get_rules()->philo[i].left_fork = &get_rules()->forks[i];
			get_rules()->philo[i].right_fork = &get_rules()->forks[(i + 1)
			% get_rules()->philo_nb];
		}
		get_rules()->philo[i].last_meal = get_rules()->start_time;
		get_rules()->philo[i].is_dead = 0;
	}
	get_rules()->someone_died = false;
	return (true);
}

bool	mutex_create(void)
{
	int	i;

	i = 0;
	allocate_resources(FORKS);
	while (i < get_rules()->philo_nb)
	{
		if (pthread_mutex_init(&get_rules()->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&get_rules()->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&get_rules()->death, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&get_rules()->meals, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&get_rules()->time, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&get_rules()->all_ate_mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	threads_create(void)
{
	int	i;

	i = -1;
	get_rules()->all_ate = false;
	while (++i < get_rules()->philo_nb)
	{
		if (pthread_create(&get_rules()->philo[i].id, NULL, routine,
				&get_rules()->philo[i]))
		{
			stop_simulation(i);
			return (false);
		}
	}
	return (true);
}
