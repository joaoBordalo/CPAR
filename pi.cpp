#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main (int argc, char *argv[])
{

	double area,pi, x;
	int i, n,j;
	char c;
	
	cout << "Numero de processadores: " << omp_get_num_procs() << endl;

	//cout << "Numero de divisoes ? "; 
	//cin >> n;
	n=10;
	for(j=10; j < 19; j++)
	{ 
	area = 0.0;
	// begin counting time
	//double begin = omp_get_wtime();
	#pragma omp parallel for private(x) reduction(+:area) num_threads (4) 
	for (i = 0; i < n; i++) {
	cout << "thread n: " << omp_get_thread_num
() << endl;
	   x = (i+0.5)/n;
	   area += 4.0/(1.0 + x*x);
	}
	
	 pi = area / n;
	// stop counting time
 	 double end = omp_get_wtime();
	//double elapsed_secs = double(end - begin);
	cout << setprecision(j) << "PI = " << pi << endl << endl;
	}
	//cout << "Time: " << elapsed_secs << endl;
	cout << "Enter para continuar ...";
	cin.get(c);
	cin.get(c);
	
}
