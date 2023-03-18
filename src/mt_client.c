/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:36:21 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/18 17:16:55 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

// void	signal_handler(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{

// 	}
// 	else if (sig == SIGUSR2)
// 	{

// 	}
// }


int	main(int argc, char *argv[])
{
	pid_t				PID;
	// struct sigaction	sa;

	// sa.sa_handler = &signal_handler;
	if (argc < 2)
		exit(1);
	PID = ft_atoi(argv[1]);
	kill(PID, SIGUSR2);
}