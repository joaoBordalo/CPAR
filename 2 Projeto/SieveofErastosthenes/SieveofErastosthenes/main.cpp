
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
//list[0] == true =>   2 => unmarked (prime)
//list[1] == true =>   3 => unmarked (prime)
//list[2] == false =>  4 => marked (not prime)

bool * markEven(bool * primes, const int primesSize)
{
	for (unsigned int i = 2; i < primesSize; i = i + 2)
	{
		primes[i] = false;
	}
	return primes;
}

bool * sequencialPrime(bool * primes, const unsigned int primesSize)
{
	primes = markEven(primes, primesSize);

	for (unsigned int i = 1; (unsigned int)pow(i + 2, 2) <= primesSize; i++)
	{
		if (primes[i] != false)
		{
			unsigned int value = (unsigned int)pow(i + 2, 2);//(i+2) ^ 2
			for (unsigned int j = value - 2; j < primesSize; j = j + i + 2)
			{
				primes[j] = false;
			}
		}

	}

	return primes;
}

bool* initListPrime(const int maxNumber)
{
	bool *list = (bool*)malloc(sizeof(bool)*(maxNumber - 1));

	for (int i = 0; i < maxNumber-1; i++)
	{
		list[i] = true;
	}
	return list;
}

int main(int args, char* argsv[])
{

	//int n = atoi(argsv[1]);
	int n;
	int op = 1;

	//do {
	cout << endl;
	cout << "1. Sequencial" << endl;
	cout << "2. Parallel shared memory" << endl;
	cout << "3. Parallel distributed memory" << endl;
	cout << "Selection?: ";

	cin >> op;
	//if (op == 0)
	//break;

	printf("Max Number: ");
	cin >> n;
	//} while (op != 0);

	bool *list = initListPrime(n);

	switch (op)
	{
	case 1:
		list = sequencialPrime(list,n-1);
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	for (unsigned int i = 0; i < n-1; i++)
	{
	cout << list[i] << " ";
	}
	//cout << list.size() << endl;
	system("pause");
	return 0;

}