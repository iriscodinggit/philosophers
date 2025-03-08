/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:57:53 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:57:55 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

bool	check_min_meals(int i)
{
	if (get_rules()->min_meals == -1)
		return (false);
	if (get_rules()->philo[i].nb_of_meals >= get_rules()->min_meals)
		return (true);
	return (false);
}

bool	dead_enough_food(int i)
{
	long	time;

	pthread_mutex_lock(&get_rules()->time);
	pthread_mutex_lock(&get_rules()->meals);
	if ((get_time_ms(&time, 1) - get_rules()->philo[i].last_meal)
		> get_rules()->time_to_die)
	{
		pthread_mutex_unlock(&get_rules()->meals);
		pthread_mutex_unlock(&get_rules()->time);
		if (check_min_meals(i))
			return (true);
		return (false);
	}
	pthread_mutex_unlock(&get_rules()->meals);
	pthread_mutex_unlock(&get_rules()->time);
	return (true);
}

bool	read_everyone_ate(void)
{
	if (get_rules()->min_meals == -1)
		return (false);
	pthread_mutex_lock(&get_rules()->all_ate_mutex);
	if (get_rules()->all_ate)
	{
		pthread_mutex_unlock(&get_rules()->all_ate_mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&get_rules()->all_ate_mutex);
		return (false);
	}
}

void	set_everyone_ate(void)
{
	pthread_mutex_lock(&get_rules()->all_ate_mutex);
	get_rules()->all_ate = true;
	pthread_mutex_unlock(&get_rules()->all_ate_mutex);
}
