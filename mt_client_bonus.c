/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:34:18 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/20 20:25:03 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_flag = 0;

static void	signal_handler(int signal)
{
	(void)signal;
	g_flag = 1;
}

static void	send_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_exit_message("ERROR - signal", EXIT_FAILURE);
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
				send_signal(pid, SIGUSR1);
			else
				send_signal(pid, SIGUSR2);
			bit_idx--;
			while (g_flag == 0)
				pause();
			g_flag = 0;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
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
