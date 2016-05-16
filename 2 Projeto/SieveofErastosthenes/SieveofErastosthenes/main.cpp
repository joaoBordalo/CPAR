
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#define MINIMUM_VALUE 25 // 2^25
#define MAXIMUM_VALUE 32 // 2^31
typedef unsigned long long ull;
using namespace std;
//list[0] == true =>   2 => unmarked (prime)
//list[1] == true =>   3 => unmarked (prime)
//list[2] == false =>  4 => marked (not prime)



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

bool* initListPrime(const ull maxNumber)
{
	bool *list = (bool*)malloc((maxNumber - 1)*sizeof(bool));

	fill_n(list, maxNumber - 1, true);
	return list;
}

int main(int args, char* argsv[])
{

	//int n = atoi(argsv[1]);
	ull n;
	int op = 1;
	bool *list;

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
		n = (ull) pow(2, MAXIMUM_VALUE);
		list = initListPrime(n);

		switch (op)
		{
		case 1:
		{

			double time = sequencialPrime(list, n - 1);

			/*for (unsigned long i = 0; i < n - 1; i++)
			{
				cout << list[i] << " ";
			}*/
			cout << "Sequencial time: " << time << endl;
			break;
		}
		case 2:
			break;
		case 3:
			break;
		case 4:
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
	system("pause");
	return 0;

}