/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:57:05 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:57:07 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

bool	write_error(char *str)
{
	int	length;

	length = 0;
	while (str[length])
	{
		length++;
	}
	write(2, str, length);
	return (length);
}
