/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:57:40 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:57:42 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	main(int ac, char **argv)
{
	if (ac < 5 || ac > 6)
		return (write_error("🍝 Ups! Please input 5 to 6 arguments.\n"));
	if (start_simulation(argv) == false)
		return (1);
	return (0);
}
