#include <omp.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <fstream>

#define MINIMUM_VALUE 25 // 2^25
#define MAXIMUM_VALUE 32 // 2^30 NOTE: in my pc can't beyond 30

//Block Decomposition Macros

#define BLOCK_LOW(i,p,n) ((i)*(n)/(p))
#define BLOCK_HIGH(i,p,n) \ (BLOCK_LOW((i)+1,p,n)-1)
#define BLOCK_SIZE(i,p,n) \ (BLOCK_LOW((i)+1,p,n)-BLOCK_LOW(i,p,n)
#define BLOCK_OWNER(index,p,n) \ ((((p)*(index)+1)-1)/(n))

typedef unsigned long long ull;
using namespace std;
//list[0] == true =>   2 => unmarked (prime)
//list[1] == true =>   3 => unmarked (prime)
//list[2] == false =>  4 => marked (not prime)


//Sequencial algorithm (DONE)
bool * markEven(bool * primes, const ull primesSize)
{
	for (ull i = 2; i < primesSize; i = i + 2)
	{
		primes[i] = false;
	}
	return primes;
}

double sequencialPrime(bool * &primes, const ull primesSize)
{
	double inicialTime, finalTime;

	inicialTime = clock();
	primes = markEven(primes, primesSize);

	for (ull i = 1; (ull)pow(i + 2, 2) <= primesSize; i++)
	{
		if (primes[i] != false)
		{
			ull value = (ull)pow(i + 2, 2);//(i+2) ^ 2
			for (ull j = value - 2; j < primesSize; j = j + i + 2)
			{
				primes[j] = false;
			}
		}

	}
	finalTime = (clock() - inicialTime) / CLOCKS_PER_SEC;
	//cout << "time: " << finalTime << endl;
	return finalTime;
}
////////////////////////////////////////////////////////////////////////////


// Parallel shared memory OpenMP algorithm (DONE)

double parallelSharedMemoryOpenMPPrime(bool * &primes, const ull primesSize, unsigned int nThreads)
{
	double inicialTime, finalTime;

	omp_set_num_threads(nThreads);

	inicialTime = omp_get_wtime();

	for (ull i = 0; (ull)pow(i + 2, 2) <= primesSize; i++)
	{
		if (primes[i] != false)
		{
			#pragma omp parallel for
			for (ull j = (ull)pow(i + 2, 2) - 2; j < primesSize; j = j + i + 2)
			{
				primes[j] = false;
			}
		}

	}

	finalTime = omp_get_wtime() - inicialTime;
	//cout << "time: " << finalTime << endl;
	return finalTime;
}

///////////////////////////////////////////////////////////////////////////


// Parallel distributed memory MPI algorithm

double parallelDistributedMemoryMPIPrime(bool * &primes, const ull primesSize)
{
	double inicialTime, finalTime;
	inicialTime = MPI_Wtime();



	finalTime = MPI_Wtime() - inicialTime;
	//cout << "time: " << finalTime << endl;
	return finalTime;
}
///////////////////////////////////////////////////////////////////////////


//  Parallel shared memory MPI algorithm

double parallelSharedMemoryMPIPrime(bool * &primes, const ull primesSize)
{
	double inicialTime, finalTime;
	inicialTime = MPI_Wtime();



	finalTime = MPI_Wtime() - inicialTime;
	//cout << "time: " << finalTime << endl;
	return finalTime;
}
///////////////////////////////////////////////////////////////////////////
bool* initListPrime(const ull maxNumber)
{
	bool *list = (bool*)malloc((maxNumber - 1)*sizeof(bool));

	//fill_n(list, maxNumber - 1, true);
	for (ull i = 0; i < maxNumber - 1; i++)
	{
		list[i] = true;
	}
	return list;
}

void outputFile(const vector <double> timers, string fileName, const unsigned int nThreads)
{
	ofstream myfile;
	fileName = fileName + ".csv";
	myfile.open(fileName.c_str());
	myfile << "Prime Value; Time (secs)" << endl;
	
	for (unsigned int i = 0,  j = MINIMUM_VALUE; i < timers.size(); i++, j++)
	{
		myfile <<"2^"<< j << ";" << timers[i] << endl;
	}
	if (nThreads != 0)
	{
		myfile << "Number Threads: ;" << nThreads;
	}
	myfile.close();
}


void initMPI(int &argc, char** &argv, int &size, int &rank)
{
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Barrier(MPI_COMM_WORLD);
}

void finalizeMPI()
{
	MPI_Finalize();
}
int main(int args, char* argsv[])
{
	//int n = atoi(argsv[1]);
	ull n;
	int op = 1, size, rank;
	bool *list;
	vector <double> timers;

	do {
		cout << endl;
		cout << "1. Sequencial" << endl;
		cout << "2. Parallel shared memory OpenMP" << endl;
		cout << "3. Parallel distributed memory MPI" << endl;
		cout << "4. Parallel shared memory MPI" << endl;
		cout << "Selection?: ";

		cin >> op;
		if (op == 0)
			break;

		//printf("Max Number: ");
		//cin >> n;
		//n = (ull) pow(2, MAXIMUM_VALUE);
		//list = initListPrime(n);

		switch (op)
		{
		case 1:
		{
			for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
			{
				n = (ull)pow(2, i);
				list = initListPrime(n);
				double time = sequencialPrime(list, n - 1);
				/*for (unsigned long i = 0; i < n - 1; i++)
				{
				cout << list[i] << " ";
				}*/
				timers.push_back(time);
				cout << "Sequencial time: " << time << endl;
				free(list);
			}
			outputFile(timers, "SequencialPrime", 0);
			timers.clear();
		}
			break;
		case 2:
		{
			unsigned int nThreads;
			cout << "Number of Threads:";
			cin >> nThreads;

			if (omp_get_max_threads() < (int) nThreads)
				nThreads =  omp_get_max_threads();

			for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
			{
				n = (ull)pow(2, i);
				list = initListPrime(n);
				double time = parallelSharedMemoryOpenMPPrime(list, n - 1, nThreads);
				/*for (unsigned long i = 0; i < n - 1; i++)
				{
				cout << list[i] << " ";
				}*/
				timers.push_back(time);
				cout << "Parallel shared memory OpenMP time: " << time << endl;
				free(list);
			}
			outputFile(timers, "ParallelSharedMemoryOpenMP", nThreads);
			timers.clear();
		}
			break;
		case 3:
		{
			initMPI(argc,argv,size,rank);
			for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
			{
				n = (ull)pow(2, i);
				list = initListPrime(n);
				double time = parallelDistributedMemoryMPIPrime(list, n - 1);
				/*for (unsigned long i = 0; i < n - 1; i++)
				{
				cout << list[i] << " ";
				}*/
				timers.push_back(time);
				cout << "Parallel distributed memory MPI time: " << time << endl;
				free(list);
			}
			finalizeMPI();
			outputFile(timers, "ParallelDistributedMemoryMPI",0);
			timers.clear();
		}
			break;
		case 4:
		{
			initMPI(argc,argv,size,rank);
			for (ull i = MINIMUM_VALUE; i <= MAXIMUM_VALUE; i++)
			{
				n = (ull)pow(2, i);
				list = initListPrime(n);
				double time = parallelSharedMemoryMPIPrime(list, n - 1);
				/*for (unsigned long i = 0; i < n - 1; i++)
				{
				cout << list[i] << " ";
				}*/
				timers.push_back(time);
				cout << "Parallel shared memory MPI time: " << time << endl;
				free(list);
			}
			finalizeMPI();
			outputFile(timers, "ParallelSharedMemoryMPI",0);
			timers.clear();
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
	return 0;

}
