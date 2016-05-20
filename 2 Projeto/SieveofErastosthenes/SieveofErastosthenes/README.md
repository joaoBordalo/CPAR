#Run in command line:
(for points 1 and 2)
>g++ main.cpp -o teste -fopenmp -O2 -Wall

>./teste

(for point 3 and running in 1 pc with 4 processes and 3 threads - the threads are doing nothing for distributed mpi)
>mpic++ mpi.cpp -o mpi -fopenmp -O2 -Wall

>mpirun -np 4 ./mpi 1 3

(for point 3 and running in 4 pcs with a total of 8 processes with 3 threads - requires hostfile in /home/.ssh directory and threads only work on shared mpi)

>mpic++ mpi.cpp -o mpi -fopenmp -O2 -Wall

>mpirun --hostfile hostfile -np 8 ./mpi 4 3
