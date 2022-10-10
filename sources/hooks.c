/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:48:44 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 21:07:07 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	move(void *param)
{
	t_info *info;

	info = param;
	if(mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if(mlx_is_key_down(info->mlx, MLX_KEY_UP)) 
		info->image->instances[0].y -= 5;
	if(mlx_is_key_down(info->mlx, MLX_KEY_DOWN)) 
		info->image->instances[0].y += 5;
	if(mlx_is_key_down(info->mlx, MLX_KEY_LEFT)) 
		info->image->instances[0].x -= 5;
	if(mlx_is_key_down(info->mlx, MLX_KEY_RIGHT)) 
		info->image->instances[0].x += 5;
	if(mlx_is_key_down(info->mlx, MLX_KEY_HOME))
	{
		info->plane.xmin = -2;
		info->plane.xmax = 1.5;
		info->plane.ymin = -1.5;
		info->plane.ymax = 1.5;
		info->iteration = 0;
		info->zoom = 1;
	}
}

void	scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_info *info;

	info = param;
	
	if (ydelta > 0)
	{
		info->zoom += 0.05;
		info->maxiters += 5;
	}
	else if (ydelta < 0)
	{
		info->zoom -=0.05;
		info->maxiters -= 5;
	}
	start(info);
}

