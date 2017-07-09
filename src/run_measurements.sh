#!/bin/bash

set -o xtrace

MEASUREMENTS=10
ITERATIONS=2
INITIAL_SIZE=8192
MAX_PROCESS=8
MESSAGE="Starting stats with: "

SIZE=$INITIAL_SIZE

NAMES=('mandelbrot_seq' 'mandelbrot_mpi' 'mandelbrot_mpi_op' 'mandelbrot_mpi_io' 'mandelbrot_mpi_io_pp' 'mandelbrot_mpi_ms')
#NAMES=('mandelbrot_seq' 'mandelbrot_mpi')

make
mkdir results

for NAME in ${NAMES[@]}; do
    mkdir results/$NAME

	for((j=1; j<=$ITERATIONS; j++)); do
		for((i=1; i<=$MAX_PROCESS; i++)); do
			if [ "$NAME" == "mandelbrot_seq" ];
			then
				if [ $i -gt 1 ];
				then
					echo "Skipping process tests for mandelbrot_seq\n"
				else
					echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> full.log 2>&1
					echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> seahorse.log 2>&1
					echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> elephant.log 2>&1
					echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> triple_spiral.log 2>&1
					perf stat -r $MEASUREMENTS ./$NAME -2.5 1.5 -2.0 2.0 $SIZE >> full.log 2>&1
					perf stat -r $MEASUREMENTS ./$NAME -0.8 -0.7 0.05 0.15 $SIZE >> seahorse.log 2>&1
					perf stat -r $MEASUREMENTS ./$NAME 0.175 0.375 -0.1 0.1 $SIZE >> elephant.log 2>&1
					perf stat -r $MEASUREMENTS ./$NAME -0.188 -0.012 0.554 0.754 $SIZE >> triple_spiral.log 2>&1
				fi
			else
				echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> full.log 2>&1
				echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> seahorse.log 2>&1
				echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> elephant.log 2>&1
				echo -e "\n$MESSAGE PROCESSES=$i, MEASUREMENTS=$MEASUREMENTS, IMGSIZE=$SIZE\n" >> triple_spiral.log 2>&1
				perf stat -r $MEASUREMENTS mpirun -np $i ./$NAME -2.5 1.5 -2.0 2.0 $SIZE >> full.log 2>&1
				perf stat -r $MEASUREMENTS mpirun -np $i ./$NAME -0.8 -0.7 0.05 0.15 $SIZE >> seahorse.log 2>&1
				perf stat -r $MEASUREMENTS mpirun -np $i ./$NAME 0.175 0.375 -0.1 0.1 $SIZE >> elephant.log 2>&1
				perf stat -r $MEASUREMENTS mpirun -np $i ./$NAME -0.188 -0.012 0.554 0.754 $SIZE >> triple_spiral.log 2>&1
			fi
		done
		SIZE=$(($SIZE * 2))
    done

    SIZE=$INITIAL_SIZE

    mv *.log results/$NAME
	mv *.ppm results/$NAME
done
