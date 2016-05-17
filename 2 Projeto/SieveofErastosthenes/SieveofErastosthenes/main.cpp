
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <fstream>

#define MINIMUM_VALUE 25 // 2^25
#define MAXIMUM_VALUE 30 // 2^30 NOTE: in my pc can't beyond 30
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

	//fill_n(list, maxNumber - 1, true);
	for (ull i = 0; i < maxNumber - 1; i++)
	{
		list[i] = true;
	}
	return list;
}

void outputFile(vector <double> timers, string fileName)
{
	ofstream myfile;
	fileName = fileName + ".csv";
	myfile.open(fileName);
	myfile << "Prime Value; Time" << endl;
	unsigned int i = 0;
	unsigned int j = MINIMUM_VALUE;
	for (; i < timers.size(); i++, j++)
	{
		myfile <<"2^"<< j << ";" << timers[i] << endl;
	}
	myfile.close();
}

int main(int args, char* argsv[])
{
	//int n = atoi(argsv[1]);
	ull n;
	int op = 1;
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
			outputFile(timers, "SequencialPrime");
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