/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:34:12 by ahorling      #+#    #+#                 */
/*   Updated: 2022/10/10 21:07:48 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

/* A simple parser to check arguments and proper values. */

int	parser(int arguments, char *argv[])
{
	if (arguments != 4)
	{
		ft_printf("Invalid input. Please configure your input as:");
		ft_printf("./fractol [fractal type] [x resolution] [y resolution]\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "Mandelbrot") != 0
		&& ft_strcmp(argv[1], "Julia") != 0
		&& ft_strcmp(argv[1], "Something") != 0)
	{
		ft_printf("Invalid fractal type. Please choose between:");
		ft_printf("'Mandelbrot', 'Julia', or 'Something'\n");
		return (1);
	}
	if (ft_atoi(argv[2]) > 1980 || ft_atoi(argv[2]) < 100)
		return (ft_printf("Please choose a x value between 100 and 1980\n"));
	if (ft_atoi(argv[3]) > 1980 || ft_atoi(argv[3]) < 100)
		return (ft_printf("Please choose a y value between 100 and 1980\n"));
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
	info->zoom = 1;
	info->maxiters = 200;

	if (ft_strcmp(fractal, "Mandelbrot") == 0)
		info->type = MANDELBROT;
	else if (ft_strcmp(fractal, "Julia") == 0)
		info->type = JULIA;
	else if (ft_strcmp(fractal, "Something") == 0)
		info->type = SOMETHING;
	info->mlx = mlx_init(info->width, info->height, fractal, false);
	if (!info->mlx)
		ft_printf("Initialization of mlx failed)");
	info->image = NULL;
}

int	main(int argc, char *argv[])
{
	t_info		info;

	if (parser(argc, argv) > 0)
		return (0);
	setup(&info, argv[1], argv[2], argv[3]);
	ft_printf("setup complete \n");
	if (!info.mlx)
		return (0);
	start(&info);
	ft_printf("start complete \n");
	mlx_scroll_hook(info.mlx, &scroll_zoom, &info);
	mlx_loop_hook(info.mlx, &move, &info);
	mlx_loop(info.mlx);
	mlx_delete_image(info.mlx, info.image);
	mlx_terminate(info.mlx);
	return (0);
}