/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zoom.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:56:08 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/17 02:33:37 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	apply_zoom(t_info *info)
{
	info->plane.xmax = zoom(info->mousepos.x, info->plane.xmax, info->zoom);
	info->plane.xmin = zoom(info->mousepos.x, info->plane.xmin, info->zoom);
	info->plane.ymax = zoom(info->mousepos.y, info->plane.ymax, info->zoom);
	info->plane.ymin = zoom(info->mousepos.y, info->plane.ymin, info->zoom);
}

long double	zoom(long double start, long double end, long double zoom)
{
	return (start + ((end - start) * zoom));
}

void	zoom_out(t_info *info)
{
	info->zoom = 1;
	if (info->zoom > 0)
		info->zoom += 0.001 * info->zoomcount;
	if (info->maxiters > 50)
		info->maxiters -= 2;
	if (info->zoomcount > 1)
		info->zoomcount -= 1;
	ft_printf("zoom count: %d\n", info->zoomcount);
}

void	zoom_in(t_info *info)
{
	if (info->zoomcount >= 230)
		ft_printf("reaching long doubles limit.\n");
	else
		ft_printf("zoom count: %d\n", info->zoomcount);
	info->zoom = 1;
	info->zoom -= 0.001 * info->zoomcount;
	info->maxiters += 2;
	info->zoomcount += 1;
}
