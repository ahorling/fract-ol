#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "fractol.h"



//********************THIS IS JUST A BUNCH OF TESTING I WAS DOING TO GET USED TO MLX.*****************************
//****************************************************************************************************************
//***************************************PLEASE IGNORE************************************************************
//****************************************************************************************************************


// ******format of the mlx_t struct*******


// typedef struct	mlx
// {
// 	void*	window; 		Window pointer, only relevent to MLX program.
// 	void*	context; 		Abstracted data only relevant to MLX & OpenGL.
// 	int32_t	width;			Current width of window, updated on resize.
// 	int32_t	height;			Current height of window, updated on resize.
// 	double	delta_time;		Time taken to draw last frame, useful to interpolations.
// }	mlx_t



// *****format of the mlx_image_t struct*****



// typedef struct mlx_image
// {
// 	const uint32_t					width;	The width of the image.
// 	const uint32_t					height;	the height of the image.
// 	uint8_t*        				pixels;	the literal pixel data.
// 	mlx_instance_t* instances;		the instance struct carries the X, Y, and Z location data.
// 	int32_t		count;				the element count of the insances array.
// 	bool		enabled;			if true the image is drawn onto the screen, else it is not.
// 	void*           context;		abstracted OpenGL data.
// }	mlx_image_t;



//***Function that opens a window and prints a single white pixel into the middle of the screen



// int	main(void)
// {
// 	mlx_t	*mlx;
// 	mlx_image_t	*g_img;

// 	mlx = mlx_init(900, 900, "Fract-ol", true); //initializes mlx. size of window width, height, window name, resizable True/False
// 	if (!mlx)
// 		exit(ft_printf("Error with mlx initialization"));
// 	g_img = mlx_new_image(mlx, 900, 900); //generates an image. Initialized mlx, width of image, height of image
// 	mlx_image_to_window(mlx, g_img, 0, 0); //adds an image to the render queue.
// 	mlx_put_pixel(g_img, 450, 450, 0xFFFFFFFF); //adds a single white pixel in the middle of the image g_img.
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, g_img); //once application requsts exit, cleanup.
// 	mlx_terminate(mlx);
// 	return (printf("closed window\n"));
// }



//****Functions make a screen full of static****



// static mlx_image_t	*g_img;

// void	hook(void* param)
// {
// 	mlx_t* mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) //if the escape key is triggered, close the window
// 		mlx_close_window(mlx);
// 	for (int x = 0; x < g_img->width; x++)
// 		for(int y = 0; y < g_img->height; y++)
// 			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
// }

// int32_t	main(void)
// {
// 	mlx_t*		mlx;

// 	mlx = mlx_init(900, 900, "Random pixels", true);
// 	if (!mlx)
// 		exit(ft_printf("Error of mlx initialization"));
// 	g_img = mlx_new_image(mlx, 900, 900);
// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// }



//*****Functions testing the hook functionality of key presses and the scroll wheel. for simplicities sake
//it is actually best to use a generic hook function as above instead of using specifically key/scroll hooks.******



// void	my_keyhook(mlx_key_data_t keydata, void* param)
// {
// 	//Pressing the J key prints 'hello'
// 	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
// 		puts("hello ");

// 	//Releasing the K key prints 'there'
// 	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
// 		puts("world");

// 	//Holding the L key prints '!'
// 	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
// 		puts("!");

// 	//making a scroll version using key presses.
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
// 		puts("up");
	
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
// 		puts("down");
// }

// void	my_scrollhook(double xdelta, double ydelta, void* param)
// {
// 	//basic up/down detection.
// 	if (ydelta > 0)
// 		puts("up");
// 	else if (ydelta < 0)
// 		puts("down");
// }

// int		main()
// {
// 	mlx_t* mlx;

// 	if (!(mlx = mlx_init(900, 900, "HOOKS", true)))
// 		exit(ft_printf("Error in mlx initialiation"));

// 	mlx_key_hook(mlx, &my_keyhook, NULL);
// 	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// }



//****Making a box and moving it around the screen. Practice for making shapes of different sizes and styles.****


t_comp	add_complex(t_comp a, t_comp b)
{
	t_comp	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_comp	subtract_complex(t_comp a, t_comp b)
{
	t_comp result;

	result.x = a.x - b.x;
	result.y = a.y + b.y;
	return (result);
}

t_comp	multiply_complex(t_comp a, t_comp b)
{
	t_comp result;

	result.x = (a.x * b.x) - (a.y * b.y);
	result.y = (a.x * b.y) + (a.y * b.x);
	return (result);
}

t_comp divide_complex(t_comp a, t_comp b)
{
	t_comp res;

	res.x = ((a.x * b.x) + (a.y * b.y)) / (pow(b.x, 2) + pow(b.y, 2));
	res.y = ((a.y * b.x) - (a.x * b.y)) / (pow(b.x, 2) + pow(b.y, 2));
	return (res);
}



mlx_image_t		*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param; 	//This sets the hook's mlx to a NULL pointer, so it does't do anythign but can still be used
					//as a paraater.
	
	if(mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if(mlx_is_key_down(param, MLX_KEY_UP)) 
		g_img->instances[0].y -= 5;			//when the up key is pressed, move the image 5 pixles up every frame while it is pressed
	if(mlx_is_key_down(param, MLX_KEY_DOWN)) 
		g_img->instances[0].y += 5;
	if(mlx_is_key_down(param, MLX_KEY_LEFT)) 
		g_img->instances[0].x -= 5;
	if(mlx_is_key_down(param, MLX_KEY_RIGHT)) 
		g_img->instances[0].x += 5;	
}



int		main()
{
	mlx_t	*mlx;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if(!(mlx = mlx_init(900, 900, "BOX", true)))
		return(ft_printf("MLX initialization error"));
	
	g_img = mlx_new_image(mlx, 900, 900);
	//ft_memset(g_img->pixels, 255, 40 * 80 * sizeof(int));	//sets pixel data. first is the transparency value (255 for totally opaque), then the size of the image, with int size data type.
	
	
	mlx_image_to_window(mlx, g_img, 200, 200); 		//Places the image g_img into the window of mlx at coords x200, y200
	mlx_loop_hook(mlx, &hook, mlx);					//passign the address of our hook function to this function allows us to move the image
	mlx_loop(mlx);
	mlx_terminate(mlx);
}