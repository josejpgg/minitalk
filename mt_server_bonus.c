/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:29:31 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/26 14:54:54 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	kill_controller(int server_pid, int signal)
{
	if (kill(server_pid, signal) == -1)
		ft_exit_message("Error KILL\n", EXIT_FAILURE);
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	character = 0;
	static int				bit = 1;
	static int				pid = 0;

	if (info->si_pid != 0)
		pid = info->si_pid;
	(void)context;
	if (signal == SIGUSR1)
		character += 0;
	if (signal == SIGUSR2)
		character += bit;
	bit <<= 1;
	if (bit == 256)
	{
		bit = 1;
		if (character == 0)
			kill_controller(pid, SIGUSR2);
		if (character != 0)
			write(1, &character, 1);
		character = 0;
	}
	kill_controller(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		ft_exit_message("Error SIGACTION\n", EXIT_FAILURE);
	ft_printf("Server PID -> %d\n", getpid());
	while (1)
		pause();
	return (0);
}
