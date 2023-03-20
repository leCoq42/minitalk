/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_talk.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:24:11 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/20 12:24:28 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

// Includes:
# include	"libft.h"
# include	"ft_printf.h"
# include	"get_next_line_bonus.h"
# include	<limits.h>
# include	<stdarg.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<signal.h>

// TO be removde
# include	<stdio.h>

long long	mt_atoi_base(const char *str, int base);

#endif