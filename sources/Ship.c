/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Ship.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 20:57:18 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:32:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	ship(t_info *info, t_comp relpoint, t_comp z)
{
	long double	bound;
	long double	temp;

	bound = sqrt((z.x * z.x) + (z.y * z.y));
	temp = 0;
	while (info->iteration < info->maxiters && bound < 2)
	{
		temp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + relpoint.x;
		z.y = 2.0 * fabsl(z.y * temp) + relpoint.y;
		bound = sqrt((z.x * z.x) + (z.y * z.y));
		info->iteration++;
	}
}
