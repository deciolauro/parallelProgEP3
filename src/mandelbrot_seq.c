/** @file 	mandelbrot_seq.c
 *	@brief	Sequential program to compute and plot mandelbrot set 
 *	
 *	C implementation of a sequential program to compute and plot some
 *  subset of a mandelbrot set adapted from the classes given by
 *  MJ Rutter (https://www.tcm.phy.cam.ac.uk/~mjr/courses/MPI/MPI.pdf)
 *
 *	Usage:
 *    ./mandelbrot_seq c_x_min c_x_max c_y_min c_y_max image_size
 *		- c_x_min: Lowest x boundary for the figure to be computed
 *		- c_x_max: Highest x boundary for the figure to be computed
 *		- c_y_mix: Lowest y boundary for the figure to be computed
 *		- c_y_max: Highest y boundary for the figure to be computed
 *		- image_size: The resolution of the resulting image
 *  Usage examples:
 *      Full Picture:         ./mandelbrot_seq -2.5 1.5 -2.0 2.0 11500
 *      Seahorse Valley:      ./mandelbrot_seq -0.8 -0.7 0.05 0.15 11500
 *      Elephant Valley:      ./mandelbrot_seq 0.175 0.375 -0.1 0.1 11500
 *      Triple Spiral Valley: ./mandelbrot_seq -0.188 -0.012 0.554 0.754 11500
 *
 *	Notes:
 *      Although we made modifications, this code is heavily based on the
 *		class examples provided by MJ Rutter.
 *		Because of that, in any event of license and copyright conflict, the
 *		license/copyright provided by Mr. Rutter TAKE PRECEDENCE OVER the
 *		GPLv3 on which this code was released.
 *
 *	@author		Decio Lauro Soares (deciolauro@gmail.com)
 *	@date		05 Jul 2017
 *	@bug		No known bugs
 *	@warning	Based on class given by MJ Rutter(May contain Copyright issues)
 * 	@copyright	GNU Public License v3
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define MAX_ITER 300
#define ESCAPE_RADIUS_SQUARED 4


/**
 * @brief Perform the calculations for the set until divergence or MAX_ITER 
 *
 * For the complex number z0, it performs the Mandelbrot calculation until it
 * reaches divergence or it reaches the maximum number of iterations,
 * whichever happens first, returning the number of iterations until divergence
 * or MAX_ITER
 *
 * @param z0 complex number to perform the Mandelbrot calculations
 * @return i integer with the number of iterations until divergerce or MAX_ITER
 */
int mandelbrot(complex z0)
{
	int i;
	complex z;

	z = z0;
	for(i=1; i<MAX_ITER; i++)
	{
		z=z*z+z0;
		if((creal(z)*creal(z))+(cimag(z)*cimag(z))>ESCAPE_RADIUS_SQUARED)
			break;
  	}

	return i;
}


/**
 * @brief Function responsible for printing usage instructions
 *
 * This function is responsible for printing the usage instructions
 *
 */
void print_instructions()
{
	printf("usage: ./mandelbrot_seq c_x_min c_x_max c_y_min c_y_max image_size\n");
	printf("examples with image_size = 11500:\n");
	printf("    Full Picture:         ./mandelbrot_seq -2.5 1.5 -2.0 2.0 11500\n");
	printf("    Seahorse Valley:      ./mandelbrot_seq -0.8 -0.7 0.05 0.15 11500\n");
	printf("    Elephant Valley:      ./mandelbrot_seq 0.175 0.375 -0.1 0.1 11500\n");
	printf("    Triple Spiral Valley: ./mandelbrot_seq -0.188 -0.012 0.554 0.754 11500\n");
}


int main(int argc, char** argv)
{
	double c_x_min, c_x_max, c_y_min, c_y_max, pixel_width, pixel_height;
	int i, j, image_size, i_x_max, i_y_max, *row;
	unsigned char *line;
	complex z;
	FILE *img;

	if(argc < 6)
	{
		print_instructions();
        exit(0);
    }
    else
	{
        sscanf(argv[1], "%lf", &c_x_min);
        sscanf(argv[2], "%lf", &c_x_max);
        sscanf(argv[3], "%lf", &c_y_min);
        sscanf(argv[4], "%lf", &c_y_max);
        sscanf(argv[5], "%d", &image_size);

        i_x_max           = image_size;
        i_y_max           = image_size;

        pixel_width       = (c_x_max - c_x_min) / i_x_max;
        pixel_height      = (c_y_max - c_y_min) / i_y_max;
    }

	row = malloc(image_size*sizeof(int));
	line = malloc(3*image_size*sizeof(unsigned char));
	img=fopen("mandelbrot_seq.ppm","w");
	fprintf(img, "P6\n%d %d 255\n", image_size, image_size);

	for(i=0; i<i_y_max; i++)
	{
    	for(j=0; j<i_x_max; j++)
		{
      		z=c_x_min+j*(pixel_width)+(c_y_max-i*(pixel_height))*I;
			row[j]=mandelbrot(z);
    	}

		// Fixed color scheme
		for(j=0; j<image_size; j++)
		{
      		if(row[j]<=63)
			{
        		line[3*j]=255;
        		line[3*j+1]=255-4*row[j];
				line[3*j+2]=255-4*row[j];
			}
			else
			{
				line[3*j]=255;
				line[3*j+1]=row[j]-63;
				line[3*j+2]=0;
			}
			// Default color for pixels over MAX_ITER
			if(row[j]==MAX_ITER)
			{
				line[3*j]=255;
				line[3*j+1]=255;
				line[3*j+2]=255;
			}

		}
		fwrite(line, 1, 3*image_size, img);
	}

	return 0;
}
