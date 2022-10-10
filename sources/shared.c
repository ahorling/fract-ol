/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shared.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 19:36:46 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 20:28:56 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

/*
	relative_pixel sets the current pixel to the relative point
	located on the cartesian plane that the fractal occupies.
*/

t_comp	relative_point(t_info info, t_comp pixel)
{
	t_comp	relpoint;

	pixel.x = pixel.x * ((info.plane.xmax - info.plane.xmin) / info.width);
	relpoint.x = pixel.x + info.plane.xmin;
	pixel.y = pixel.y * ((info.plane.ymax - info.plane.ymin) / info.height);
	relpoint.y = pixel.y + info.plane.ymin;
	return(relpoint);
}

/*
	draw_fractal takes the struct and the relative point on the cartesian plane, creates a
	complex number Z that will be used by the function to store results, and then paints the pixel
	depending on the result
*/

void	draw_fractal(t_info *info, t_comp relpoint, t_comp pixel)
{
	t_comp	z;

	z = relpoint;
	if (info->type == MANDELBROT)
		mandelbrot(info, relpoint, z);
	if (info->type == JULIA)
	;
	if (info->type == SOMETHING)
	;
	colour_pixel(info, pixel);
}

/*
	checks which fractal is to be printed, and begins the printing process by 
	first setting the size of the cartesian plane the fractal is to be printed on.
	then it begins moving through the image. for every pixel it finds the realtive
	point on the plane, then calls a function to print the pixel
	depending on which fractal is called and the location of the point on the plane.
*/

void	start(t_info *info)
{
	t_comp pixel;
	t_comp relpoint;

	pixel.x = 0;
	pixel.y = 0;
	if (info->image != NULL)
		mlx_delete_image(info->mlx, info->image);
	info->image = mlx_new_image(info->mlx, info->width, info->height);
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