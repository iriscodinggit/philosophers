/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:00:40 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 18:00:44 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

long	get_time_ms(long *time, int returning)
{
	struct timeval	tv;
	long			millisecs;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write_error("🍝 Ups! Could not get the current time!\n");
		return (-1);
	}
	millisecs = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (time)
		*time = millisecs;
	if (returning == 1)
		return (millisecs);
	return (-1);
}

void	get_time_mutex(long *time)
{
	pthread_mutex_lock(&get_rules()->time);
	get_time_ms(time, 0);
	pthread_mutex_unlock(&get_rules()->time);
}

long	time_passed(long *start, long *current)
{
	long	elapsed;

	elapsed = *current - *start;
	return (elapsed);
}

void	extra_death_check(t_philo *philo, long current_time)
{
	long	elapsed;

	pthread_mutex_lock(&get_rules()->death);
	get_rules()->someone_died = true;
	philo->is_dead = true;
	pthread_mutex_unlock(&get_rules()->death);
	elapsed = time_passed(&get_rules()->start_time, &current_time);
	printf("%ld %d is dead\n", elapsed, philo->index);
}

void	wait_time(long action_time, t_philo *philo)
{
	long	current_time;
	long	start;

	get_time_mutex(&start);
	while (true)
	{
		pthread_mutex_lock(&get_rules()->death);
		if (get_rules()->someone_died || philo->is_dead)
		{
			pthread_mutex_unlock(&get_rules()->death);
			break ;
		}
		pthread_mutex_unlock(&get_rules()->death);
		get_time_mutex(&current_time);
		if ((current_time - philo->last_meal) >= get_rules()->time_to_die)
		{
			extra_death_check(philo, current_time);
			break ;
		}
		usleep(100);
		if ((current_time - start) >= action_time)
			break ;
	}
}
