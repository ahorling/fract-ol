/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 19:34:16 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 21:02:49 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

/*
	the purpose of mandelbrot is to cycle through the function z = z^2 + c, and then
	returning the number of iterations required to break out of the bounds of our
	cartesian plane. iterations refer to how many times the function has been done,
	while C is our point on the cartesian plane
*/

void	mandelbrot(t_info *info, t_comp relpoint, t_comp z)
{
	double	bound;
	double	temp;

	bound = sqrt((z.x * z.x) + (z.y * z.y));
	temp = 0;
	while (info->iteration < info->maxiters && bound < 4)
	{
		temp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + relpoint.x;
		z.y = (2 * temp * z.y) + relpoint.y;
		bound = sqrt((z.x * z.x) + (z.y * z.y));
		info->iteration++;
	}
}
