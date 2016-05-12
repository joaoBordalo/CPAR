
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
//list[0] == true =>   2 => unmarked (prime)
//list[1] == true =>   3 => unmarked (prime)
//list[2] == false =>  4 => marked (not prime)

vector <bool> markEven(vector <bool> primes)
{
	for (unsigned int i = 2; i < primes.size(); i = i + 2)
	{
		primes[i] = false;
	}
	return primes;
}

vector <bool> sequencialPrime(vector <bool> primes)
{
	primes = markEven(primes);

	for (unsigned int i = 1; (unsigned int)pow(i + 2, 2) <= primes.size(); i++)
	{
		if (primes[i] != false)
		{
			unsigned int value = (unsigned int)pow(i + 2, 2);//(i+2) ^ 2
			for (unsigned int j = value - 2; j < primes.size(); j = j + i + 2)
			{
				primes[j] = false;
			}
		}

	}

	return primes;
}

vector <bool> initListPrime(int maxNumber)
{
	vector<bool> list;

	for (int i = 2; i <= maxNumber; i++)
	{
		list.push_back(true);
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

	vector <bool> list = initListPrime(n);

	switch (op)
	{
	case 1:
		list = sequencialPrime(list);
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	/*for (unsigned int i = 0; i < list.size(); i++)
	{
	cout << list[i] << " ";
	}*/
	//cout << list.size() << endl;
	system("pause");
	return 0;

}