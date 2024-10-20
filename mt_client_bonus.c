/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:34:18 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/20 14:33:30 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sent_message(int pid, char *str)
{
	int	bit_idx;

	while (*str)
	{
		bit_idx = 7;
		while (bit_idx >= 0)
		{
			if (*str >> bit_idx & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit_idx--;
			pause();
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		ft_exit_message("ERROR", EXIT_FAILURE);
	else
	{
		pid = ft_atoi(argv[1]);
		sent_message(pid, argv[2]);
	}
	return (0);
}
