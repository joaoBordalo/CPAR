#include <omp.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <mpi.h>

#define MINIMUM_VALUE 25 // 2^25
#define MAXIMUM_VALUE 32 // 2^30 NOTE: in my pc can't beyond 30

//Block Decomposition Macros

#define BLOCK_LOW(i,p,n) (i)*(n)/(p)
#define BLOCK_HIGH(i,p,n) (BLOCK_LOW((i)+1,p,n)-1)
#define BLOCK_SIZE(i,p,n) (BLOCK_LOW((i)+1,p,n)-BLOCK_LOW(i,p,n))
#define BLOCK_OWNER(index,p,n) ((((p)*(index)+1)-1)/(n))

typedef unsigned long long ull;
using namespace std;
//list[0] == true =>   2 => unmarked (prime)
//list[1] == true =>   3 => unmarked (prime)
//list[2] == false =>  4 => marked (not prime)


bool* initListPrime(const ull maxNumber)
{
	bool *list = (bool*)malloc((maxNumber)*sizeof(bool));

	//fill_n(list, maxNumber , true);
	for (ull i = 0; i < maxNumber; i++)
	{
		list[i] = true;
	}
	return list;
}

///////////////////////////////////////////////////////////////////////////


// Parallel distributed memory MPI algorithm

double parallelDistributedMemoryMPIPrime(ull value, ofstream & file, int nPCs, int &rank)
{
	int size;
	ull counter=0, primesn=0;
	bool * primes;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ull primesSize = pow(2,value);
	ull blockSize = BLOCK_SIZE(rank, size, primesSize-1);
	ull lowValue = BLOCK_LOW(rank,size,primesSize-1)+2;
	ull highValue = BLOCK_HIGH(rank,size,primesSize-1)+2;
	ull startBlockValue;
	double inicialTime=0, finalTime=0;
	
	primes = initListPrime(blockSize);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0)
	{
		inicialTime = MPI_Wtime();
	}

	for (ull i = 2; (ull)pow(i , 2) <= primesSize;)
	{
		if (pow(i,2) < lowValue)
		{
			if((lowValue) % (i) == 0)
			{
				startBlockValue = lowValue;
			}
			else
			{
				startBlockValue = lowValue + ((i) - (lowValue % (i)));
			}
		}
		else
		{
			startBlockValue = pow(i,2);
		}
		
			for (ull j = startBlockValue ; j <= highValue; j = j + i)
			{
				primes[j-lowValue] = false;
			}
			
			if(rank == 0)
			{	
				do{
					i++;
				}while(!primes[i-lowValue] && pow(i,2) < highValue);
			}
			MPI_Bcast(&i, 1,MPI_UNSIGNED_LONG,0,MPI_COMM_WORLD);
		}
	
	
	if(rank == 0)
	{
		finalTime = MPI_Wtime() - inicialTime;
		file << nPCs << ";" << size/nPCs << ";"<<"2^" << value << ";"<< finalTime <<endl;
	}
	
	for(ull i = 0; i < blockSize;i++)
	{
		if(primes[i])
		counter++;
	}
	
	if(size>1)
	{
		MPI_Reduce(&counter,&primesn,1,MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD); 
	}
	else
		primesn= counter;
	
	
	if(rank == 0)
	cout << primesn << endl;
	
	
	free(primes);
	return finalTime;
}
///////////////////////////////////////////////////////////////////////////


//  Parallel shared memory MPI algorithm

double parallelSharedMemoryMPIPrime(const ull value, ofstream & file, int nPCs, int & rank, int threads)
{
	int size;
	ull counter=0, primesn=0;
	bool * primes;
	omp_set_num_threads(threads);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ull primesSize = pow(2,value);
	ull blockSize = BLOCK_SIZE(rank, size, primesSize-1);
	ull lowValue = BLOCK_LOW(rank,size,primesSize-1)+2;
	ull highValue = BLOCK_HIGH(rank,size,primesSize-1)+2;
	ull startBlockValue;
	double inicialTime=0, finalTime=0;
	
	primes = initListPrime(blockSize);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0)
	{
		inicialTime = MPI_Wtime();
	}

	for (ull i = 2; (ull)pow(i , 2) <= primesSize;)
	{
		if (pow(i,2) < lowValue)
		{
			if((lowValue) % (i) == 0)
			{
				startBlockValue = lowValue;
			}
			else
			{
				startBlockValue = lowValue + ((i) - (lowValue % (i)));
			}
		}
		else
		{
			startBlockValue = pow(i,2);
		}
			#pragma omp parallel for 
			for (ull j = startBlockValue ; j <= highValue; j = j + i)
			{
				primes[j-lowValue] = false;
			}
			
			if(rank == 0)
			{	
				do{
					i++;
				}while(!primes[i-lowValue] && pow(i,2) < highValue);
			}
			MPI_Bcast(&i, 1,MPI_UNSIGNED_LONG,0,MPI_COMM_WORLD);
		}
	
	
	if(rank == 0)
	{
		finalTime = MPI_Wtime() - inicialTime;
		file << nPCs << ";" << size/nPCs << ";"<<"2^" << value << ";"<< finalTime <<endl;
	}
	
	for(ull i = 0; i < blockSize;i++)
	{
		if(primes[i])
		counter++;
	}
	
	if(size>1)
	{
		MPI_Reduce(&counter,&primesn,1,MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD); 
	}
	else
		primesn= counter;
	
	
	if(rank == 0)
	cout << primesn << endl;
	
	
	free(primes);
	return finalTime;
}
///////////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	ofstream file;
	int rank=0;
	MPI_Init(&argc,&argv);
	int op = 1;

	do {
		cout << endl;
		cout << "1. Parallel distributed memory MPI" << endl;
		cout << "2. Parallel shared memory MPI" << endl;
		cout << "Selection?: ";

		cin >> op;
		if (op == 0)
			break;

		switch (op)
		{
		case 1:
		{
			file.open("ParallelDistributedMemoryMPI.csv", ios::app);
			if(rank == 0)
				file << "Nº pcs" << ";" << "Nº Processes / pc" << ";" << "Prime Value" << ";" << "Time (secs)" << endl;
			for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
			{
				//n =(ull)pow(2, i);
				double time = parallelDistributedMemoryMPIPrime(i,file,atoi(argv[1]),rank);
				cout << "\nParallel distributed memory MPI time: " << time << endl;
			}
			if(rank == 0)
				file << endl << endl;
			file.close();
		}
			break;
		case 2:
		{
			file.open("ParallelSharedMemoryMPI.csv", ios::app);
			if(rank == 0)
				file << "Nº pcs" << ";" << "Nº Processes / pc" << ";" << "Prime Value" << ";" << "Time (secs)" << endl;
			int j = atoi(argv[2]);
				for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
				{
					double time = parallelSharedMemoryMPIPrime(i,file, atoi(argv[1]), rank,j);
					cout << "Parallel shared memory MPI time: " << time << endl;
				}
				if(rank == 0)
					file << "Number Threads: "<< j << endl;
			if(rank == 0)
				file << endl << endl;
			file.close();
		}
			break;
		default:
			break;
		}
	} while (op != 0);

	/*for (unsigned int i = 0; i < n - 1; i++)
	{
		cout << list[i] << " ";
	}*/
	//cout << list.size() << endl;
	//system("pause");
		MPI_Finalize();
	return 0;

}
