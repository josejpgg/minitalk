/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:28:59 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/26 14:56:08 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	kill_controller(int server_pid, int signal)
{
	if (kill(server_pid, signal) == -1)
		ft_exit_message("Error KILL\n", EXIT_FAILURE);
}

static void	send_end_str(int server_pid)
{
	static int	i = 0;

	if (i <= 8)
		kill_controller(server_pid, SIGUSR1);
	i++;
}

static void	send_signal(int server_pid, char *str)
{
	static int	bit = 0;
	static char	*str_bit = 0;

	if (str)
		str_bit = str;
	if (*str_bit)
	{
		if (*str_bit >> bit & 1)
			kill_controller(server_pid, SIGUSR2);
		else
			kill_controller(server_pid, SIGUSR1);
		bit++;
		if (bit == 8)
		{
			str_bit++;
			bit = 0;
		}
	}
	if (!(*str_bit))
		send_end_str(server_pid);
}

static void	signal_handler(int signal, siginfo_t *info, void *content)
{
	static int	server_pid = 0;

	(void)content;
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (signal == SIGUSR1)
		send_signal(server_pid, NULL);
	if (signal == SIGUSR2)
		ft_exit_message("Message received by server\n", EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	int					pid;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		ft_exit_message("Error SIGACTION\n", EXIT_FAILURE);
	if (argc != 3)
		ft_exit_message("Usage: ./client [PID] [message]\n", EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		ft_exit_message("Invalid PID\n", EXIT_FAILURE);
	send_signal(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
