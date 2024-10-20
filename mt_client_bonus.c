/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:34:18 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/20 18:56:46 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int flag = 0;

void	signal_handler(int signal)
{
	(void)signal;
	flag = 1;
}

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
			while (flag == 0)
				pause();
			flag = 0;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction	sa;

	if (argc != 3)
		ft_exit_message("ERROR", EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_exit_message("ERROR", EXIT_FAILURE);
	sent_message(pid, argv[2]);
	return (0);
}
