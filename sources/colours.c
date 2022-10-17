/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:19:21 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:38:20 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	encode_rgba_mand(t_info info)
{
	t_rgb	rgb;

	rgb.a = 255;
	rgb.r = 0;
	rgb.g = 2 * info.iteration;
	rgb.b = 3 * info.iteration;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

int	encode_rgba_julia(t_info info)
{
	t_rgb	rgb;

	rgb.a = 255;
	rgb.r = info.iteration * 10;
	rgb.g = info.iteration * 5;
	rgb.b = info.iteration * 1;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

int	encode_rgba_ship(t_info info)
{
	t_rgb	rgb;

	rgb.a = 255;
	rgb.r = info.iteration * 15;
	rgb.g = info.iteration;
	rgb.b = info.iteration * 6;
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | rgb.a);
}

void	colour_pixel(t_info *info, t_comp pixel)
{
	if (info->iteration == info->maxiters)
		mlx_put_pixel(info->image, pixel.x, pixel.y, 255);
	else if (info->iteration <= info->maxiters && info->type == mandel)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba_mand(*info));
	else if (info->iteration <= info->maxiters && info->type == jul)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba_julia(*info));
	else if (info->iteration <= info->maxiters && info->type == burningship)
		mlx_put_pixel(info->image, pixel.x, pixel.y, encode_rgba_ship(*info));
}
