/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:35:08 by rcesar-d          #+#    #+#             */
/*   Updated: 2024/11/15 14:46:32 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_bin_to_char(int signal, char *c)
{
	if (signal == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signal == SIGUSR2)
		*c <<= 1;
}

void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static int	pid;
	static char	c;
	static int	bits;

	(void)context;
	if (pid != 0 && pid != info->si_pid)
		return ;
	if (pid == 0)
		pid = info->si_pid;
	ft_bin_to_char(signal, &c);
	if (++bits == 8)
	{
		bits = 0;
		if (c == '\0')
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Welcome to rcesar's server!\n");
	ft_printf("Use this PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 \
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_putstr_fd("Error sigaction\n", 1), 1);
	while (1)
		pause();
	return (0);
}

/* 

Encryption

Server Side:

Each signal updates c:

Start with c = 00000000

•	After Bit 7 (0): c = 00000000
•	After Bit 6 (1): c = 00000001
•	After Bit 5 (0): c = 00000010
•	After Bit 4 (0): c = 00000100
•	After Bit 3 (0): c = 00001000
•	After Bit 2 (0): c = 00010000
•	After Bit 1 (0): c = 00100000
•	After Bit 1 (0): c = 01000001

	After all 8 bits, c = 01000001, which is ASCII 65 or 'A'

*/