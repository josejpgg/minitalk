/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:48:36 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/26 00:33:12 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_end_str(int server_pid)
{
	static int i = 0;

	if (i <= 8)
		if (kill(server_pid, SIGUSR1) == -1)
			ft_exit_message("Error KILL\n", EXIT_FAILURE);
	i++;
}

void send_signal(int server_pid, char *str)
{
	static int bit = 0;
	static char *str_bit = 0;

	if (str)
		str_bit = str;
	if (*str_bit)
	{
		// if (*str_bit >> bit & 1)
		// 	if (kill(pid, SIGUSR2) == -1)
		// 		ft_exit_message("Error KILL\n", EXIT_FAILURE);
		// if (!(*str_bit >> bit & 1))
		// 	if (kill(pid, SIGUSR1) == -1)
		// 		ft_exit_message("Error KILL\n", EXIT_FAILURE);
		if ((((unsigned char)*str_bit >> bit) % 2) == 0)
			if (kill(server_pid, SIGUSR1) == -1)
				ft_exit_message("Error KILL\n", EXIT_FAILURE);
		if ((((unsigned char)*str_bit >> bit) % 2) == 1)
			if (kill(server_pid, SIGUSR2) == -1)
				ft_exit_message("Error KILL\n", EXIT_FAILURE);
		bit++;
		if (bit == 8)
		{
			str_bit++;
			bit = 0;
		}
	}
	if (!(*str_bit))
		send_end_str(server_pid);
	// else
	// {
	// 	send_end_str(pid);
	// }
}

void signal_handler(int signal, siginfo_t *info, void *content)
{
	static int server_pid;

	 (void)content;
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (signal == SIGUSR1)
		send_signal(server_pid, NULL);
	if (signal == SIGUSR2)
	{
		write(1, "Message received by server\n", 28);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	struct sigaction action;
	int pid;

	// action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &action, 0) == -1 || sigaction(SIGUSR2, &action, 0) == -1)
		ft_exit_message("Error SIGACTION\n", EXIT_FAILURE);
	if (argc != 3)
	{
		write(1, "Usage: ./client [PID] [message]\n", 31);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0)
	{
		write(1, "Invalid PID\n", 12);
		return (1);
	}
	send_signal(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
