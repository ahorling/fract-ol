/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:34:12 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/19 16:26:13 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	julia_parse(t_info *info, int arguments, char *argv[])
{
	t_comp	julia_c;

	if (arguments == 2 || arguments == 4)
		info->juliaconst = (t_comp){.x = -1.476, .y = 0};
	else if (arguments == 6)
	{
		info->width = ft_atoi(argv[2]);
		info->height = ft_atoi(argv[3]);
		info->plane = (t_plane){.xmin = -2, .xmax = 2, .ymin = -2, .ymax = 2};
		if (ft_atoi(argv[4]) < 0 || ft_atoi(argv[4]) > info->width)
			return (ft_printf("optional julia pixel must be in window.\n"));
		if (ft_atoi(argv[5]) < 0 || ft_atoi(argv[5]) > info->height)
			return (ft_printf("optional julia pixel must be in window.\n"));
		julia_c = (t_comp){.x = ft_atoi(argv[4]), .y = ft_atoi(argv[5])};
		info->juliaconst = relative_point(*info, julia_c);
	}
	else
	{
		ft_printf("Invalid Julia input. please configure your input as:");
		ft_printf("./fractol Julia [pixel coord 1] [pixel coord 2]");
		ft_printf("{x between 1980 and 100} {y between 1980 and 100}\n");
		return (1);
	}
	return (0);
}

int	parser(t_info *info, int arguments, char *argv[])
{
	if (ft_strcmp(argv[1], "Julia") == 0)
		return (julia_parse(info, arguments, argv));
	if (arguments != 4 && arguments != 2 && arguments != 6)
	{
		ft_printf("Invalid input. Please configure your input as:");
		ft_printf("./fractol [fractal type] [x resolution] [y resolution]\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "Mandelbrot") != 0
		&& ft_strcmp(argv[1], "Julia") != 0
		&& ft_strcmp(argv[1], "Ship") != 0)
	{
		ft_printf("Invalid fractal type. Please choose between:");
		ft_printf("'Mandelbrot', 'Julia', or 'Ship'\n");
		return (1);
	}
	if (arguments != 2)
	{
		if (ft_atoi(argv[2]) > 1980 || ft_atoi(argv[2]) < 100)
			return (ft_printf("Please choose a x value between 100 and 1980\n"));
		if (ft_atoi(argv[3]) > 1980 || ft_atoi(argv[3]) < 100)
			return (ft_printf("Please choose a y value between 100 and 1980\n"));
	}
	return (0);
}

/* 
	setting up the mlx image and window, as well as setting what fractal was chosen
	to be displayed.
*/

void	setup(t_info *info, char *fractal, char *x, char *y)
{
	info->width = ft_atoi(x);
	info->height = ft_atoi(y);
	reset_view(info);
	if (ft_strcmp(fractal, "Mandelbrot") == 0)
		info->type = mandel;
	else if (ft_strcmp(fractal, "Julia") == 0)
		info->type = jul;
	else if (ft_strcmp(fractal, "Ship") == 0)
		info->type = burningship;
	info->mlx = mlx_init(info->width, info->height, fractal, false);
	if (!info->mlx)
		ft_printf("Initialization of mlx failed)");
	info->image = mlx_new_image(info->mlx, info->width, info->height);
}

int	main(int argc, char *argv[])
{
	t_info		info;

	if (parser(&info, argc, argv) > 0)
		return (0);
	if (argc == 2)
		setup(&info, argv[1], "700", "700");
	else
		setup(&info, argv[1], argv[2], argv[3]);
	if (!info.mlx)
		return (0);
	start(&info);
	mlx_scroll_hook(info.mlx, &scroll_zoom, &info);
	mlx_loop_hook(info.mlx, &hooks, &info);
	mlx_loop(info.mlx);
	mlx_delete_image(info.mlx, info.image);
	mlx_terminate(info.mlx);
	return (0);
}
