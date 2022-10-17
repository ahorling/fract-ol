/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:48:44 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:37:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	reset_view(t_info *info)
{
	info->plane.xmin = -2;
	info->plane.xmax = 2;
	info->plane.ymin = -2;
	info->plane.ymax = 2;
	info->iteration = 0;
	info->zoom = 1;
	info->zoomcount = 1;
	info->maxiters = 200;
	info->mousepos = (t_comp){.x = 0.0, .y = 0.0};
	info->juliaconst = (t_comp){.x = -1.476, .y = 0};
}

void	shift_view(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP))
	{
		info->plane.ymin -= 0.1 / info->zoomcount;
		info->plane.ymax -= 0.1 / info->zoomcount;
		info->zoom = 1;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
	{
		info->plane.ymin += 0.05 / info->zoomcount;
		info->plane.ymax += 0.05 / info->zoomcount;
		info->zoom = 1;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->plane.xmin -= 0.05 / info->zoomcount;
		info->plane.xmax -= 0.05 / info->zoomcount;
		info->zoom = 1;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->plane.xmin += 0.05 / info->zoomcount;
		info->plane.xmax += 0.05 / info->zoomcount;
		info->zoom = 1;
	}
	start(info);
}

void	hooks(void *param)
{
	t_info	*info;
	int		a;
	int		b;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(info->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(info->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		shift_view(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_HOME))
	{
		reset_view(info);
		start(info);
	}
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& info->type == jul)
	{
		mlx_get_mouse_pos(info->mlx, &a, &b);
		info->juliaconst = (t_comp){.x = a, .y = b};
		info->juliaconst = relative_point(*info, info->juliaconst);
		start(info);
	}
}

void	scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_info	*info;
	int		x;
	int		y;

	x = 0;
	y = 0;
	info = param;
	mlx_get_mouse_pos(info->mlx, &x, &y);
	info->mousepos.x = x;
	info->mousepos.y = y;
		info->mousepos = relative_point(*info, info->mousepos);
	if (ydelta > 0)
		zoom_out(info);
	else if (ydelta < 0)
		zoom_in(info);
	start(info);
}
