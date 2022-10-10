/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zoom.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:56:08 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 21:06:58 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	apply_zoom(t_info *info)
{
	info->plane.xmin = -2;
	info->plane.xmax = 1.5;
	info->plane.ymin = -1.5;
	info->plane.ymax = 1.5;

	info->plane.xmax = info->plane.xmax * info->zoom;
	info->plane.xmin = info->plane.xmin * info->zoom;
	info->plane.ymax = info->plane.ymax * info->zoom;
	info->plane.ymin = info->plane.ymin * info->zoom;
}