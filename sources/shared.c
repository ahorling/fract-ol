/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shared.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 19:36:46 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:37:36 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

t_comp	relative_point(t_info info, t_comp pixel)
{
	t_comp	relpoint;

	pixel.x = pixel.x * ((info.plane.xmax - info.plane.xmin) / info.width);
	relpoint.x = pixel.x + info.plane.xmin;
	pixel.y = pixel.y * ((info.plane.ymax - info.plane.ymin) / info.height);
	relpoint.y = (pixel.y + info.plane.ymin);
	return (relpoint);
}

void	draw_fractal(t_info *info, t_comp relpoint, t_comp pixel)
{
	t_comp	z;

	z = relpoint;
	if (info->type == mandel)
		mandelbrot(info, relpoint, z);
	if (info->type == jul)
		julia(info, z);
	if (info->type == burningship)
		ship(info, relpoint, z);
	colour_pixel(info, pixel);
}

void	start(t_info *info)
{
	t_comp	pixel;
	t_comp	relpoint;

	pixel.x = 0;
	pixel.y = 0;
	if (info->zoomcount >= 250)
	{
		ft_printf("stopping you there\n");
		return ;
	}
	apply_zoom(info);
	while (pixel.y < info->height)
	{
		while (pixel.x < info->width)
		{
			relpoint = relative_point(*info, pixel);
			draw_fractal(info, relpoint, pixel);
			pixel.x++;
			info->iteration = 0;
		}
		pixel.y++;
		pixel.x = 0;
	}
	mlx_image_to_window(info->mlx, info->image, 0, 0);
}
