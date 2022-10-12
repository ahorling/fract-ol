/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:19:21 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/12 21:14:34 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int encode_rgba_mand(t_info info)
{
	t_rgb	rgb;
	double	factor;
	
	factor = (double)info.iteration / info.maxiters;
	rgb.a = 255;
	rgb.r = 255 * factor * info.iteration * 0.2;
	rgb.g = 255 * factor * info.iteration * 0.5;
	rgb.b = 255 * factor * info.iteration * 2;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

int encode_rgba_julia(t_info info, t_comp pixel)
{
	t_rgb	rgb;

	rgb.a = 255;
	rgb.r = info.iteration * 1;
	rgb.g = info.iteration * 2;
	rgb.b = info.iteration * 3;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

void	colour_pixel(t_info *info, t_comp pixel)
{
	if (info->iteration == info->maxiters)
		mlx_put_pixel(info->image, pixel.x, pixel.y, 255);
	else if (info->iteration <= info->maxiters && info->type == MANDELBROT)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba_mand(*info));
	else if (info->iteration <= info->maxiters && info->type == JULIA)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba_julia(*info, pixel));
}
