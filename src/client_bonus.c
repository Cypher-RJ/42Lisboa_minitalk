/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:02:39 by rcesar-d          #+#    #+#             */
/*   Updated: 2024/11/15 14:49:49 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int	g_sign_sent;

void	sig_handler(int sign, siginfo_t *info, void *context)
{
	static int	bits;

	(void)context;
	(void)info;
	(void)sign;
	g_sign_sent = true;
	if (sign == SIGUSR2)
		bits++;
	else if (sign == SIGUSR1)
		ft_printf("Received %d bytes\n", bits / 8);
}

int	ft_char_to_bin(char c, int pid)
{
	int	i;
	int	bit_i;

	bit_i = 7;
	while (bit_i >= 0)
	{
		i = 0;
		if ((c >> bit_i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_sign_sent == false)
		{
			if (i == 5)
			{
				ft_putstr_fd("Server does not respond.\n", 1);
				exit(0);
			}
			i++;
			usleep(10000000);
		}
		g_sign_sent = false;
		bit_i--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					byte_i;
	int					pid;

	if (ac != 3)
	{
		ft_printf("You passed %d args, you need to pass 2.\n", ac - 1);
		return (1);
	}
	byte_i = 0;
	pid = ft_atoi(av[1]);
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (pid < 0 || kill(pid, 0) == -1)
		return (ft_printf("check your pid \n"));
	if (sigaction(SIGUSR1, &sa, NULL) == -1 \
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_putstr_fd("Sigaction error\n", 1), 1);
	while (av[2][byte_i])
		ft_char_to_bin(av[2][byte_i++], pid);
	ft_char_to_bin('\0', pid);
	return (0);
}
