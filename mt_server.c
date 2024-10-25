// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mt_server.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/25 20:48:32 by jgamarra          #+#    #+#             */
// /*   Updated: 2024/10/26 00:22:56 by jgamarra         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minitalk.h"

// void signal_handler(int signal, siginfo_t *info, void *context)
// {
// 	static unsigned char character = 0;
// 	static int bit = 1;
// 	static int pid = 0;

// 	if (info->si_pid != 0)
// 		pid = info->si_pid;
// 	(void)context;
// 	if (signal == SIGUSR1)
// 		character += 0;
// 	if (signal == SIGUSR2)
// 		character += bit;
// 	bit <<= 1;
// 	if (bit == 256)
// 	{
// 		bit = 1;
// 		if (character == 0)
// 			if (kill(pid, SIGUSR2) == -1)
// 				ft_exit_message("Error KILL\n", EXIT_FAILURE);
// 		if (character != 0)
// 			write(1, &character, 1);
// 		character = 0;
// 	}
// 	if (kill(pid, SIGUSR1) == -1)
// 		ft_exit_message("Error KILL\n", EXIT_FAILURE);
// }

// int main(void)
// {
// 	struct sigaction action;
// 	int pid;

// 	// action.sa_flags = SA_SIGINFO;
// 	action.sa_sigaction = signal_handler;
// 	pid = getpid();
// 	if (sigaction(SIGUSR1, &action, NULL) == -1 || sigaction(SIGUSR2, &action, NULL) == -1)
// 		ft_exit_message("Error SIGACTION\n", EXIT_FAILURE);
// 	write(1, "Server PID: ", 12);
// 	ft_putnbr_fd(pid, 1);
// 	write(1, "\n", 1);
// 	while (1)
// 		pause();
// 	return (0);
// }

#include "minitalk.h"

void	ft_error_handler(int i)
{
	if (i == 0)
	{
		write(1, "Error KILL\n", 12);
		exit(1);
	}
	if (i == 1)
	{
		write(1, "Error SIGACTION\n", 17);
		exit(1);
	}
}

void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	val = 0;
	static int				bit = 1;
	static int				id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		val += 0;
	if (sig == SIGUSR2)
		val += bit;
	bit <<= 1;
	if (bit == 256)
	{
		bit = 1;
		if (val == 0)
			if (kill(id, SIGUSR2) == -1)
				ft_error_handler(0);
		if (val != 0)
			write(1, &val, 1);
		val = 0;
	}
	if (kill(id, SIGUSR1) == -1)
		ft_error_handler(0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_signal_handler;
	pid = getpid();
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		ft_error_handler(1);
		return (1);
	}
	write(1, "PID = ", 6);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
