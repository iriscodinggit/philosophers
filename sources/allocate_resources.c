/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_resources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:56:34 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:56:40 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	allocate_resources(t_alloc_type resource)
{
	pthread_mutex_t	*forks;
	t_philo			*philosophers;

	if (resource == FORKS)
	{
		forks = ft_calloc(sizeof(pthread_mutex_t), get_rules()->philo_nb);
		if (!forks)
			return ;
		get_rules()->forks = forks;
	}
	else if (resource == PHILOS)
	{
		philosophers = ft_calloc(sizeof(t_philo), get_rules()->philo_nb);
		if (!philosophers)
			return ;
		get_rules()->philo = philosophers;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	ptr = NULL;
	total_size = count * size;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	if (count != 0 && total_size / count != size)
		return (NULL);
	ptr = malloc (total_size);
	if (!ptr)
		return (NULL);
	if (ptr != NULL)
	{
		ft_bzero(ptr, size * count);
		return (ptr);
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}
