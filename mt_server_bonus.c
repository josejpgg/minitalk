/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgamarra <jgamarra@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:34:18 by jgamarra          #+#    #+#             */
/*   Updated: 2024/10/20 14:39:54 by jgamarra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal, siginfo_t *siginfo)
{
	static int	bit_idx;
	static int	character;

	if (signal == SIGUSR1)
	{
		character |= 1 << (7 - bit_idx);
		kill(siginfo->si_pid, SIGUSR1);
	}
	bit_idx++;
	if (bit_idx == 8)
	{
		ft_putchar_fd(character, 1);
		bit_idx = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_exit_message("ERROR", EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_exit_message("ERROR", EXIT_FAILURE);
	sa.sa_flags = 0;
	ft_printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
