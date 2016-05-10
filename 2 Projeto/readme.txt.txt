2.	The	Sieve	of	Erastosthenes
The Sieve of Eratosthenes is a simple algorithm to find the prime numbers up to a given number n.
Consider the following implementations:
(i) sequential, on a single CPU-core;
(ii) parallel, on a shared memory system, using OpenMP;
(iii) parallel, on a distributed memory system using only MPI and MPI with the shared memory
version.
The following steps describe the algorithm:
1. Create list of unmarked natural numbers 2, 3, …, n
2. k ← 2
3. Repeat
(a) Mark all multiples of k between k2 and n
(b) k ← smallest unmarked number > k
 until k2 > n
4. The unmarked numbers are primes
The time complexity of the algorithm is Θ(n ln ln n).
Data range to consider (n): from 225 to 232