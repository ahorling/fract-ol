/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zoom.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:56:08 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/14 20:46:05 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	apply_zoom(t_info *info)
{
	info->plane.xmax = info->plane.xmax / info->zoom;
	info->plane.xmin = info->plane.xmin / info->zoom;
	info->plane.ymax = info->plane.ymax / info->zoom;
	info->plane.ymin = info->plane.ymin / info->zoom;
}

void	zoom_out(t_info *info)
{
	info->zoom = 1;
	if(info->zoom > 0)
		info->zoom -= 0.01 * info->zoomcount;
	info->maxiters -= 1;
	if (info->zoomcount > 1)
		info->zoomcount -= 1;
}

void	zoom_in(t_info *info)
{
	info->zoom = 1;
	info->zoom += 0.01 * info->zoomcount;
	info->maxiters += 1;
	info->zoomcount += 1;
}