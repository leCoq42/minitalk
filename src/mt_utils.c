/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 11:14:33 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/20 14:32:23 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

long long	mt_atoi_base(const char *str, int base)
{
	long long	val;
	int			sign;

	val = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str > 47 && *str < 58)
		val = val * base + (*str++ - 48);
	if (val < 0 || val > LLONG_MAX)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	return (val * sign);
}
