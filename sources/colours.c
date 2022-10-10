/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:19:21 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 21:25:19 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int encode_rgba(t_info info)
{
	t_rgb	rgb;

	rgb.a = 255;
	rgb.r = info.iteration * 2;
	rgb.g = info.iteration * 1;
	rgb.b = info.iteration * 1.5;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

void	colour_pixel(t_info *info, t_comp pixel)
{
	if (info->iteration == info->maxiters)
		mlx_put_pixel(info->image, pixel.x, pixel.y, 255);
	else if (info->iteration <= info->maxiters)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba(*info));
}
