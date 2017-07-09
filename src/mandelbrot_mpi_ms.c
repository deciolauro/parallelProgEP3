/** @file 	mandelbrot_mpi_ms.c
 *	@brief	Open MPI C implementation to compute and plot mandelbrot set
 *	
 *	Open MPI C implementation of a program to compute and plot
 *  some subset of a mandelbrot set adapted from the classes given by
 *  MJ Rutter (https://www.tcm.phy.cam.ac.uk/~mjr/courses/MPI/MPI.pdf)
 *  using the Master/Slave paradigm
 *
 *	Usage:
 *    mpirun -np NP ./mandelbrot_mpi_ms c_x_min c_x_max c_y_min c_y_max image_size
 *		- NP: Number of Open MPI processes
 *		- c_x_min: Lowest x boundary for the figure to be computed
 *		- c_x_max: Highest x boundary for the figure to be computed
 *		- c_y_mix: Lowest y boundary for the figure to be computed
 *		- c_y_max: Highest y boundary for the figure to be computed
 *		- image_size: The resolution of the resulting image
 *  Usage examples:
 *      Full Picture: mpirun -np 4 ./mandelbrot_mpi_ms -2.5 1.5 -2.0 2.0 11500
 *      Seahorse Valley: mpirun -np 4 ./mandelbrot_mpi_ms -0.8 -0.7 0.05 0.15 8192
 *      Elephant Valley: mpirun -np 8 ./mandelbrot_mpi_ms 0.175 0.375 -0.1 0.1 800
 *      TS Valley: mpirun -np 2 ./mandelbrot_mpi_ms -0.188 -0.012 0.554 0.754 400
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
#include <mpi.h>

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
	printf("usage: mpirun -np NP ./mandelbrot_mpi_ms c_x_min c_x_max c_y_min c_y_max image_size\n");
	printf("examples with image_size = 11500:\n");
	printf("    Full Picture: mpirun -np 4 ./mandelbrot_mpi_ms -2.5 1.5 -2.0 2.0 11500\n");
	printf("    Seahorse Valley: mpirun -np 8 ./mandelbrot_mpi_ms -0.8 -0.7 0.05 0.15 11500\n");
	printf("    Elephant Valley:  mpirun -np 2 ./mandelbrot_mpi_ms 0.175 0.375 -0.1 0.1 11500\n");
	printf("    Triple Spiral Valley: mpirun -np 8 ./mandelbrot_mpi_ms -0.188 -0.012 0.554 0.754 11500\n");
}


int main(int argc, char** argv)
{
	double c_x_min, c_x_max, c_y_min, c_y_max, pixel_width, pixel_height;
	int i, j, image_size, i_x_max, i_y_max, rank, nproc, hdr, r, s, nslaves;
	int msg, *row;
	unsigned char *line;
	complex z;
	FILE *img;
	MPI_Status st;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	nslaves=nproc-1;

	if(nslaves<1)
	{
		printf("Unable to run Master/Slave paradigm with 0 slaves");
		exit(0);
	}

	if(argc < 6)
	{
		if(rank==0)
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

	row=malloc(image_size*sizeof(int));
	line=malloc(3*image_size*sizeof(unsigned char));
	img=fopen("mandelbrot_mpi_ms.ppm", "w");

	// Master code
	if(rank==0)
	{
		img=fopen("mandelbrot_mpi_ms.ppm", "w");
    	hdr=fprintf(img, "P6\n%d %d 255\n", image_size, image_size);

		for(i=0; i<nslaves; i++)
			MPI_Send(&i, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);

		for(i=0; i<image_size; i++)
		{
			MPI_Recv(line, 3*image_size, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);

			r=st.MPI_TAG;
			s=st.MPI_SOURCE;
			fseek(img, hdr+3*image_size*r, SEEK_SET);
			fwrite(line, 1, 3*image_size, img);

			if((i+nslaves)<image_size)
				msg=i+nslaves;
			else
				msg=-1;

			MPI_Send(&msg, 1, MPI_INT, s, 0, MPI_COMM_WORLD);
		}
	}
	// Slave
	else
	{
		for(;;)
		{
			MPI_Recv(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

			// If received message -1, close the slave
			if(i==-1)
				break;

			for(j=0; j<i_x_max; j++)
			{
				z=c_x_min+j*(pixel_width)+(c_y_max-i*(pixel_height))*I;
				row[j]=mandelbrot(z);
			}

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
				if(row[j]==MAX_ITER)
				{
					line[3*j]=255;
					line[3*j+1]=255;
					line[3*j+2]=255;
				}
			}

			MPI_Send(line, 3*image_size, MPI_CHAR, 0, i, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
