/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 19:00:07 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:01:59 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	julia(t_info *info, t_comp z)
{
	long double bound;
	long double temp;

	bound = sqrt((z.x * z.x) + (z.y * z.y));
	temp = 0;
	while(info->iteration < info->maxiters && bound < 4)
	{
		temp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + info->juliaconst.x;
		z.y = (2 * z.y * temp) + info->juliaconst.y;
		bound = sqrt((z.x * z.x) + (z.y * z.y));
		info->iteration++;
	}
}