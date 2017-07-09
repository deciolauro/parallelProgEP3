OT = mandelbrot

CC = gcc
MPICC = mpicc
CFLAGS = -Wall -Wpedantic -Werror -ggdb -pg
MPIFLAGS = -Wall -Wpedantic -Werror
CC_OPT = -std=c11

CC_OMP = -fopenmp
CC_PTH = -pthread

.PHONY: all
all: $(OT)_seq $(OT)_mpi $(OT)_mpi_op $(OT)_mpi_io $(OT)_mpi_io_pp $(OT)_mpi_ms

$(OT)_seq: $(OT)_seq.c
	$(CC) $(CFLAGS) -o $(OT)_seq $(CC_OPT) $(OT)_seq.c

$(OT)_mpi: $(OT)_mpi.c
	$(MPICC) $(MPIFLAGS) -o $(OT)_mpi $(OT)_mpi.c

$(OT)_mpi_op: $(OT)_mpi_op.c
	$(MPICC) $(MPIFLAGS) -o $(OT)_mpi_op $(OT)_mpi_op.c

$(OT)_mpi_io: $(OT)_mpi_io.c
	$(MPICC) $(MPIFLAGS) -o $(OT)_mpi_io $(OT)_mpi_io.c

$(OT)_mpi_io_pp: $(OT)_mpi_io_pp.c
	$(MPICC) $(MPIFLAGS) -o $(OT)_mpi_io_pp $(OT)_mpi_io_pp.c

$(OT)_mpi_ms: $(OT)_mpi_ms.c
	$(MPICC) $(MPIFLAGS) -o $(OT)_mpi_ms $(OT)_mpi_ms.c

.PHONY: clean

clean:
	rm -f $(OT)_seq $(OT)_mpi $(OT)_mpi_op $(OT)_mpi_io
	rm -f $(OT)_mpi_io_pp $(OT)_mpi_ms *.ppm
